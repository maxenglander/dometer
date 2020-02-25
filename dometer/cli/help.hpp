#pragma once

#include <ostream>

namespace dometer::cli {
    class Help {
        public:
            static void printHelp();
            static void printHelp(std::ostream&);
    };
}
