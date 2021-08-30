// networklayer.cpp

#include <network.hpp>
#include <utility>


NetworkLayer::Network::Network(const ContextPtr &context_ptr, IPAddress connectionIP): m_context_ptr(context_ptr),
                                                                                       m_connectionIP(std::move(connectionIP)),
                                                                                       m_stream(*m_context_ptr){

}

void NetworkLayer::Network::send(const std::string &city_name, const std::string &token) {

    std::string target = generateTarget(city_name, token);

    int version = 11;

    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, m_connectionIP.host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    send(req);

}

std::string NetworkLayer::Network::receive() {

    return boost::beast::buffers_to_string(p_receive().body().data());

}

bool NetworkLayer::Network::start() {

    tcp::resolver resolver(*m_context_ptr);

    try {
        auto const results = resolver.resolve(m_connectionIP.host/*"localhost"*/, m_connectionIP.port);
        m_stream.connect(results);
    }catch(...) {
        std::cout << "Can't reach server";
        return false;
    }

    return m_stream.socket().is_open();
}

std::string NetworkLayer::Network::generateTarget(const std::string & city_name, const std::string & token) const {
    std::string target;

    target = "https://" + m_connectionIP.host + "/data/2.5/weather?"
           + "q=" + city_name
           + "&appid=" + token
           + "&units=metric";

    return target;
}

void NetworkLayer::Network::send(const http::request<http::string_body> &request) {

     if(!m_errors) {

         http::write(m_stream, request, m_errors);

     }

}

http::response<http::dynamic_body> NetworkLayer::Network::p_receive() {

    beast::flat_buffer buffer;

    http::response<http::dynamic_body> res;

    if(!m_errors) {

        http::read(m_stream, buffer, res, m_errors);

    }

    return res;
}

NetworkLayer::Network::~Network() {

    if(!m_errors) {

        m_stream.socket().shutdown(tcp::socket::shutdown_both, m_errors);

    }

}



