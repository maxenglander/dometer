#include <iostream>
#include <ostream>

#include "dometer/main/help.hpp"

namespace dometer::main {
    void Help::printHelp() {
        printHelp(std::cerr);
    }

    void Help::printHelp(std::ostream& os) {
        os << "Dometer." << std::endl;
        os << std::endl;
        os << "Usage:" << std::endl;
        os << "  dometer --config=<path>" << std::endl;
        os << "  dometer --help" << std::endl;
        os << std::endl;
        os << "Options:" << std::endl;
        os << "  --config=<file>  Supply configuration file [default: /etc/dometer/config.json]." << std::endl;
        os << "  --help           Show this help message." << std::endl;
    }
}
