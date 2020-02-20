#include "config/config.hpp"
#include "config/config_parser.hpp"
#include "config/dns/dns_parser.hpp"
#include "config/metrics/metrics_parser.hpp"
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
