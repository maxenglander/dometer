#pragma once

#include "dometer/cli/options.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::cli {
    class options_parser {
        public:
            static std::x::expected<options, util::error> parse(int argc, char** argv);
    };
}
