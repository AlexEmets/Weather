#pragma once
#include"network.hpp"
#include <boost/property_tree/json_parser.hpp>
using boost::property_tree::ptree;
namespace ClientLayer
{
    using tcp = NetworkLayer::tcp;

//    std::istringstream iss(R"({
//        "topology_1": {
//            "clnt_id": "aldgdsgsd",
//            "sensors": {
//                "num_sensors": "6",
//                "sensor_1": {
//                    "time_interval": "5#15",
//                    "min_bound": "",
//                    "max_bound": "54",
//                    "anomaly": "2%",
//                    "anomaly_window": "70",
//                    "jump": "10",
//                    "topic": "sense/thubrahali/temp",
//                    "qos": "1"
//                }
//            }
//        }
//    })");



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



        std::string outputResponse(const std::string& serverResponse);

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