#pragma once

#include <memory>
#include <string>

#include "dometer/app/options.hpp"
#include "dometer/config/dns/parser.hpp"
#include "dometer/config/metrics/parser.hpp"
#include "dometer/util/error.hpp"
#include "json/json.h"
#include "std/x/expected.hpp"

namespace app = dometer::app;
namespace util = dometer::util;

namespace dometer::config {
    class InternalParser {
        public:
            InternalParser();
            InternalParser(dometer::config::dns::Parser,
                                dometer::config::metrics::Parser);
            app::Options fromJson(const Json::Value&) const;
        private:
            const dometer::config::dns::Parser dnsParser;
            const dometer::config::metrics::Parser metricsParser;
    };
}
