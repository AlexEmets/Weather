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
    m_connection->start();

    m_connection->send(m_city_name, m_token);

    m_connection->receive();

    std::cout << outputResponse();
}

std::string ClientLayer::Client::outputResponse() {
    return std::string();
}


