#pragma once

#include <vector>

#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler {
    class HandlerFactory {
        public:
            static std::x::expected<Handler, util::Error> makeHandler(Options options);
            static std::x::expected<std::vector<Handler>, util::Error> makeHandlers(std::vector<Options> options);
    };
}
