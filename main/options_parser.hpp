#pragma once

#include "util/error.hpp"
#include "main/options.hpp"
#include "x/expected.hpp"

namespace util = dometer::util;

namespace dometer::main {
    class OptionsParser {
        public:
            static std::x::expected<Options, util::Error> parse(int argc, char** argv);
    };
}
