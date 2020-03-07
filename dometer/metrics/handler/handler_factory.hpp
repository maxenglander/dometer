#pragma once

#include <vector>

#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler {
    class handler_factory {
        public:
            static std::x::expected<handler, util::error> make_handler(options options);
            static std::x::expected<std::vector<handler>, util::error> make_handlers(std::vector<options> options);
    };
}
