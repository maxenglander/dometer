#pragma once

#include <ostream>

namespace dometer::cli {
    class help {
        public:
            static void print_help();
            static void print_help(std::ostream&);
    };
}
