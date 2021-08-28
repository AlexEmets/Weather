// client.cpp

#include <client.hpp>


void ClientLayer::Client::setCity(const std::string &city_name) {
    m_city_name = city_name;
}

void ClientLayer::Client::setToken(const std::string &token) {
    m_token = token;
}

ClientLayer::Client::Client(const NetworkLayer::ContextPtr &context_ptr, std::string host, std::string port)
            : m_connection(new NetworkLayer::Network(context_ptr, {host, port})){
    ;
}

std::string ClientLayer::Client::getCity() const {
    return std::string(m_city_name);
}

std::string ClientLayer::Client::getToken() const {
    return std::string(m_token);
}

