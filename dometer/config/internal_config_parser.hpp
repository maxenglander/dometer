#pragma once

#include <memory>
#include <string>

#include "dometer/app/options.hpp"
#include "dometer/config/dns/dns_parser.hpp"
#include "dometer/config/metrics/metrics_parser.hpp"
#include "dometer/util/error.hpp"
#include "json/json.h"
#include "std/x/expected.hpp"

namespace app = dometer::app;
namespace util = dometer::util;

namespace dometer::config {
    class InternalConfigParser {
        public:
            InternalConfigParser();
            InternalConfigParser(dometer::config::dns::DnsParser,
                                dometer::config::metrics::MetricsParser);
            app::Options fromJson(const Json::Value&) const;
        private:
            const dometer::config::dns::DnsParser dnsParser;
            const dometer::config::metrics::MetricsParser metricsParser;
    };
}
