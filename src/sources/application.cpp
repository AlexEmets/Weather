// application.cpp

#include <application.hpp>
#include <iostream>

Application::Application(int argc, char* argv[]):argc(argc), argv(argv) {}

int Application::exec() {
    boost::program_options::options_description options("Program options");

    options.add_options()
            ("help,h", "Show help")
            ("city,c", "Enter city")
            ("token,t", "Enter token")
            ("address,a", boost::program_options::value<std::string>()->default_value("api.openweathermap.org"), "Enter host address")
            ("port,p", boost::program_options::value<std::string>()->default_value("80"), "Enter port")
            ;

    boost::program_options::variables_map variablesMap;
    try {
        boost::program_options::store(boost::program_options::parse_command_line(this->argc, this->argv, options), variablesMap);
    }catch(...) {
        std::cerr<<"Parse error";
        return 1;
    }
    if(variablesMap.count("help")) {
        std::cout << options;
    }

}

