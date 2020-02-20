#include "dometer/config/config.hpp"
#include "dometer/config/config_parser.hpp"
#include "dometer/config/dns/dns_parser.hpp"
#include "dometer/config/metrics/metrics_parser.hpp"
#include "rapidjson/document.h"

namespace dometer::config {
    ConfigParser::ConfigParser()
        :   ConfigParser::ConfigParser(dometer::config::dns::DnsParser(),
                                         dometer::config::metrics::MetricsParser()) {}

    ConfigParser::ConfigParser(dometer::config::dns::DnsParser dnsParser,
                                 dometer::config::metrics::MetricsParser metricsParser)
        :    dnsParser(dnsParser),
             metricsParser(metricsParser) {}

}
