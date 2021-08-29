// application.cpp

#include "application.hpp"
#include <iostream>
#include <memory>
#include <fstream>
std::string readTokenFromFile(const std::string& fileName) {
    std::ifstream inFile;
    std::string fileToken;
    inFile.open("/home/oleksandr/Weather/token.txt");
    char fikeCharacter;
    while (inFile >> fikeCharacter) {
        fileToken += fikeCharacter;
    }
    return fileToken;
}

Application::Application(int argc, char* argv[]):argc(argc), argv(argv) {}

int Application::exec() {
    boost::program_options::options_description options("Program options");

    options.add_options()
            ("help,h", "Show help")
            ("city,c",boost::program_options::value<std::string>(), "Enter city")
            ("token,t", boost::program_options::value<std::string>(), "Enter token")
            ("address,a", boost::program_options::value<std::string>()->default_value("api.openweathermap.org"), "Enter host address")
            ("port,p", boost::program_options::value<std::string>()->default_value("80"), "Enter port")
            ;

    boost::program_options::variables_map variablesMap;

    try {
        boost::program_options::store(boost::program_options::parse_command_line(this->argc, this->argv, options), variablesMap);
    }catch(...) {
        std::cerr<<"Parse error";
        return 0;
    }


//    try {
//        boost::program_options::notify(variablesMap);
//    } catch (std::exception& e) {
//        std::cerr << "Error: " << e.what() << "\n";
//        return 1;
//    }


    std::shared_ptr<boost::asio::io_context> ioc_shared;
    ClientLayer::Client client(std::make_shared<boost::asio::io_context>(),
                               variablesMap["address"].as<std::string>(),
                               variablesMap["port"].as<std::string>());


    //variablesMap.size()==2 => there are only default values in the map(no arguments are written)
    if(variablesMap.count("help") || variablesMap.size()==2) {
        std::cout << options;
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

   // std::cout << '\n' << "city: " << client.getCity() << "\n" << "token: " << client.getToken() << '\n';

    client.process();

    return 0;
}

