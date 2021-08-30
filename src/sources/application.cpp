// application.cpp

#include "application.hpp"
#include <memory>
#include <iostream>
#include <filesystem>

//it works if we execute program from,for example, cmake-build-debug/, build/ directories(not from project root)
std::string readTokenFromFile(const std::string& fileName) {
    namespace fs = std::filesystem;

    fs::path currentPath = fs::current_path();
    fs::path tokenPath = currentPath.remove_filename().append("token.txt");

    std::ifstream tokenFile;
    tokenFile.open(tokenPath);

    std::string fileToken;
    char fileCharacter;
    while (tokenFile >> fileCharacter) {
        fileToken += fileCharacter;
    }

    return fileToken;
}

Application::Application(int argc, char* argv[]):argc(argc), argv(argv) {}

int Application::exec() {
    boost::program_options::options_description options("Options");

    std::string defaultPort = "80";
    std::string defaultAddress = "api.openweathermap.org";

    options.add_options()
            ("help,h", "Show help")
            ("city,c",boost::program_options::value<std::string>(), "Enter city (If the city name is divided into several \n"
                                                                    "words - use _ instead of space)")
            ("token,t", boost::program_options::value<std::string>(), "Enter token")
            ("address,a", boost::program_options::value<std::string>(), "Enter host address")
            ("port,p", boost::program_options::value<std::string>(), "Enter port")
            ;

    boost::program_options::variables_map variablesMap;

    try {

        boost::program_options::store(boost::program_options::parse_command_line(this->argc, this->argv, options), variablesMap);

    }catch(...) {

        return 0;

    }

    if(variablesMap.count("address")) {

        defaultAddress = variablesMap["address"].as<std::string>();

    }


    if(variablesMap.count("port")) {

        defaultPort = variablesMap["port"].as<std::string>();

    }

    std::shared_ptr<boost::asio::io_context> ioc_shared;
    ClientLayer::Client client(std::make_shared<boost::asio::io_context>(),
                               defaultAddress,
                               defaultPort);



    if(variablesMap.count("help") || variablesMap.empty()) {
        std::cout << options;
        return 0;
    }

    if(!variablesMap.count("token")) {
        client.setToken(readTokenFromFile("token.txt"));
    }


    if(variablesMap.count("city"))
    {
        client.setCity(variablesMap["city"].as<std::string>());
    }

    if(variablesMap.count("token"))
    {
        client.setToken(variablesMap["token"].as<std::string>());
    }

    try {

        client.process();

    }catch(...) {

        std::cout << "Can't get weather in " << client.getCity();
        return 1;

    }
    return 0;
}

