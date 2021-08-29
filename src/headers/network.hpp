#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

namespace NetworkLayer
{
    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace ip = boost::asio::ip;
    using tcp = ip::tcp;
    using ContextPtr = std::shared_ptr<boost::asio::io_context>;

    typedef struct IPAddress
    {
        std::string host;
        std::string port;
    } IPAddress;

    //std::string target;

    class Network
    {
    public:
        /**
         * @brief Ctor
         * @param context_ptr - smart pointer to io_context
         * @param connectionIP - structure that contains host and port for connection
         * */
        Network(const ContextPtr& context_ptr, IPAddress connectionIP);

        /**
         * @brief Connection to server
         * @returns successful connection
         * */
        bool start();

        /**
         * @brief Prepare request and call send
         * */
        void send(const std::string & city_name, const std::string & token);
        std::string generateTarget(const std::string & city_name, const std::string & token) const;
        /**
         * @brief Convert response to string
         * @returns Server response
         * */
        std::string receive();

    private:
        ContextPtr m_context_ptr;
        IPAddress m_connectionIP;
        std::string m_target;
        beast::tcp_stream m_stream;
        /**
         * @brief Send request to connectionIP
         * @param request - ready for send request
         * */
        void send(const http::request<http::string_body> & request);

        /**
         * @brief Receive server response
         * @returns server response
         * */
        http::response<http::dynamic_body> p_receive();
    };
}