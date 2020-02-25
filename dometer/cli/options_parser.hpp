#pragma once

#include "dometer/cli/options.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::cli {
    class OptionsParser {
        public:
            static std::x::expected<Options, util::Error> parse(int argc, char** argv);
    };
}
