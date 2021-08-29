// networklayer.cpp

#include <network.hpp>
#include <utility>


NetworkLayer::Network::Network(const ContextPtr &context_ptr, IPAddress connectionIP): m_context_ptr(context_ptr),
                                                                                       m_connectionIP(std::move(connectionIP)){

}

void NetworkLayer::Network::send(const std::string &city_name, const std::string &token) {

}

std::string NetworkLayer::Network::receive() {
    return std::string();
}

bool NetworkLayer::Network::start() {
    return false;
}

