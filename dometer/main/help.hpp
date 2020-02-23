#pragma once

#include <ostream>

namespace dometer::main {
    class Help {
        public:
            static void printHelp();
            static void printHelp(std::ostream&);
    };
}
