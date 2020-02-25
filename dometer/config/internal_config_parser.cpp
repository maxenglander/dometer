#include <cassert>
#include <memory>

#include "dometer/app/options.hpp"
#include "dometer/config/internal_config_parser.hpp"
#include "dometer/util/error.hpp"
#include "json/json.h"
#include "std/x/expected.hpp"

namespace app = dometer::app;
namespace util = dometer::util;

namespace dometer::config {
    InternalConfigParser::InternalConfigParser()
        : InternalConfigParser(dometer::config::dns::DnsParser(),
                       dometer::config::metrics::MetricsParser()) {}

    InternalConfigParser::InternalConfigParser(dometer::config::dns::DnsParser dnsParser,
                               dometer::config::metrics::MetricsParser metricsParser)
        : dnsParser(dnsParser),
          metricsParser(metricsParser) {}

    app::Options InternalConfigParser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("dns"));
        assert(jsonValue["dns"].isObject());
        assert(jsonValue.isMember("metrics"));
        assert(jsonValue["metrics"].isObject());
        return app::Options{
            dnsParser.fromJson(jsonValue["dns"]),
            metricsParser.fromJson(jsonValue["metrics"])
        };
    }
}
