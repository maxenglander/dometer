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
    class internal_parser {
        public:
            internal_parser();
            internal_parser(dometer::config::dns::parser,
                                dometer::config::metrics::parser);
            app::options from_json(const Json::Value&) const;
        private:
            const dometer::config::dns::parser dns_parser;
            const dometer::config::metrics::parser metrics_parser;
    };
}
