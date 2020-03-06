#include <iostream>
#include <ostream>

#include "dometer/cli/help.hpp"

namespace dometer::cli {
    void help::print_help() {
        print_help(std::cerr);
    }

    void help::print_help(std::ostream& os) {
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
