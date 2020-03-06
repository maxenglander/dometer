#include <cassert>
#include <memory>

#include "dometer/app/options.hpp"
#include "dometer/config/internal_parser.hpp"
#include "dometer/util/error.hpp"
#include "json/json.h"
#include "std/x/expected.hpp"

namespace app = dometer::app;
namespace util = dometer::util;

namespace dometer::config {
    InternalParser::InternalParser()
        : InternalParser(dometer::config::dns::parser(),
                       dometer::config::metrics::parser()) {}

    InternalParser::InternalParser(dometer::config::dns::parser dnsParser,
                               dometer::config::metrics::parser metricsParser)
        : dnsParser(dnsParser),
          metricsParser(metricsParser) {}

    app::options InternalParser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("dns"));
        assert(jsonValue["dns"].isObject());
        assert(jsonValue.isMember("metrics"));
        assert(jsonValue["metrics"].isObject());
        return app::options{
            dnsParser.fromJson(jsonValue["dns"]),
            metricsParser.fromJson(jsonValue["metrics"])
        };
    }
}
