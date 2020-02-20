#pragma once

#include "dometer/main/options.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::main {
    class OptionsParser {
        public:
            static std::x::expected<Options, util::Error> parse(int argc, char** argv);
    };
}
