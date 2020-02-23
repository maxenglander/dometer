#pragma once

#include <memory>
#include <string>

#include "dometer/config/config.hpp"
#include "dometer/config/dns/dns_parser.hpp"
#include "dometer/config/metrics/metrics_parser.hpp"
#include "json/json.h"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

using namespace std::x;
namespace util = dometer::util;

namespace dometer::config {
    class InternalConfigParser {
        public:
            InternalConfigParser();
            InternalConfigParser(dometer::config::dns::DnsParser,
                                dometer::config::metrics::MetricsParser);
            Config fromJson(const Json::Value&) const;
        private:
            const dometer::config::dns::DnsParser dnsParser;
            const dometer::config::metrics::MetricsParser metricsParser;
    };
}
