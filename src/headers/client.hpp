#pragma once
#include"network.hpp"
namespace ClientLayer
{
    using tcp = NetworkLayer::tcp;

    class Client
    {
    public:
        /**
         * @brief Ctor
         * @param context_ptr - smart pointer to io_context
         * @param host - server address
         * @param port - server port
         * */
        Client(const NetworkLayer::ContextPtr & context_ptr, std::string host, std::string port);

        /**
         * @brief Main function that connections to server, sends request and shows result
         * */
        void process();



        std::string outputResponse();

        void setCity(const std::string & city_name);
        void setToken(const std::string & token);

        std::string getCity() const;
        std::string getToken() const;

    private:
        std::shared_ptr<NetworkLayer::Network> m_connection;

        std::string m_city_name;
        std::string m_token;
    };
}