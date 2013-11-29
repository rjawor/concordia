#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

#include "concordia/concordia.hpp"
#include "build/libdivsufsort/include/divsufsort.h"

namespace po = boost::program_options;

int main(int argc, char** argv) {
    po::options_description desc("Allowed options");

    desc.add_options()
        ("help,h", "Display this message")
        ("config,c", boost::program_options::value<std::string>(),
                                 "Concordia configuration file (required)");

    po::variables_map cli;
    po::store(po::parse_command_line(argc, argv, desc), cli);
    po::notify(cli);

    if (cli.count("help")) {
        std::cerr << desc << std::endl;
        return 1;
    }

    std::string configFile;
    if (cli.count("config")) {
        configFile = cli["config"].as<std::string>();
    } else {
        std::cerr << "No Concordia configuration file given. Terminating."
                                                                << std::endl;
        return 1;
    }


    try {
        Concordia concordia(configFile);
        std::cout << "Welcome to Concordia. Version = "
                  << concordia.getVersion() << endl;
    } catch(ConcordiaException & e) {
        std::cerr << "ConcordiaException caught with message: "
                  << std::endl
                  << e.what()
                  << std::endl
                  << "Terminating execution."
                  << std::endl;
        return 1;
    } catch(exception & e) {
        std::cerr << "Exception caught with message: "
                  << std::endl
                  << e.what()
                  << std::endl
                  << "Terminating execution."
                  << std::endl;
        return 1;
    }

    return 0;
}
