// networklayer.cpp

#include <network.hpp>
#include <utility>


NetworkLayer::Network::Network(const ContextPtr &context_ptr, IPAddress connectionIP): m_context_ptr(context_ptr),
                                                                                       m_connectionIP(std::move(connectionIP)),
                                                                                       m_stream(*m_context_ptr){

}

void NetworkLayer::Network::send(const std::string &city_name, const std::string &token) {
    std::string target = generateTarget(city_name, token);
    //std::string target = "https://api.openweathermap.org/data/2.5/weather?q=Kyiv&appid=292633d2713150012cac0d4434220325";

    int version = 11;

    // Set up an HTTP GET request message
    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, m_connectionIP.host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    send(req);

    //std::cout << "\ntarget:" << target << "\n";
}

std::string NetworkLayer::Network::receive() {

    return boost::beast::buffers_to_string(p_receive().body().data());

}

bool NetworkLayer::Network::start() {


    // These objects perform our I/O
    tcp::resolver resolver(*m_context_ptr);


    // Look up the domain name
    auto const results = resolver.resolve(m_connectionIP.host, m_connectionIP.port);


    // Make the connection on the IP address we get from a lookup
    try {
        m_stream.connect(results);
    }catch(...) {
        return false;
    }

    return m_stream.socket().is_open();
}

std::string NetworkLayer::Network::generateTarget(const std::string & city_name, const std::string & token) const {
    return "https://" + m_connectionIP.host + "/data/2.5/weather?"
           + "q=" + city_name
           + "&appid=" + token
           + "&units=metric";

}

void NetworkLayer::Network::send(const http::request<http::string_body> &request) {

     //Send the HTTP request to the remote host
     if(!m_errors) {
         http::write(m_stream, request);
     }
}

http::response<http::dynamic_body> NetworkLayer::Network::p_receive() {

    // This buffer is used for reading and must be persisted
    beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::dynamic_body> res;

    // Receive the HTTP response
    http::read(m_stream, buffer, res);


    return res;
}

NetworkLayer::Network::~Network() {
    m_stream.socket().shutdown(tcp::socket::shutdown_both, m_errors);
}



