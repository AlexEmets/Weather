// client.cpp

#include <client.hpp>
#include <utility>
#include <iostream>



void ClientLayer::Client::setCity(const std::string &city_name) {
    m_city_name = city_name;
}

void ClientLayer::Client::setToken(const std::string &token) {
    m_token = token;
}

ClientLayer::Client::Client(const NetworkLayer::ContextPtr &context_ptr, std::string host, std::string port)
            : m_connection(new NetworkLayer::Network(context_ptr, {std::move(host), std::move(port)})){




}

std::string ClientLayer::Client::getCity() const {
    return std::string(m_city_name);
}

std::string ClientLayer::Client::getToken() const {
    return std::string(m_token);
}

void ClientLayer::Client::process() {
    if(m_connection->start()) {

        m_connection->send(m_city_name, m_token);
        std::string serverResponse = m_connection->receive();

        std::cout << outputResponse(serverResponse);
    }
}

std::string ClientLayer::Client::outputResponse(const std::string& serverResponse) {

    std::string responseTemplate = "City: %1%\n"
                                   "Temperature: %2%°C\n"
                                   "Wind's speed: %3% meter/sec\n"
                                   "Wind's direction: %4%°\n";
    try {
        std::istringstream iss(serverResponse);
        ptree document;
        read_json(iss, document);

        auto oss = boost::format(responseTemplate) %
                   document.get<std::string>("name") %
                   document.get<double>("main.temp") %
                   document.get<double>("wind.speed") %
                   document.get<int>("wind.deg");

        return oss.str();
    }catch(const boost::property_tree::ptree_error& exc) {
        return "Can't get weather in " + this->m_city_name + '\n';
    }
}


