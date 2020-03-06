#include <cassert>

#include "dometer/config/metrics/handler/prometheus/pull_transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/pull_transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    dometer::metrics::handler::prometheus::PullTransportOptions PullTransportParser::fromJson(
            const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("bindAddress"));
        assert(jsonValue["bindAddress"].isString());
        assert(jsonValue.isMember("numThreads"));
        assert(jsonValue["numThreads"].isUInt());
        assert(jsonValue.isMember("metricsPath"));
        assert(jsonValue["metricsPath"].isString());

        return dometer::metrics::handler::prometheus::PullTransportOptions{
            jsonValue["bindAddress"].asString(),
            jsonValue["metricsPath"].asString(),
            jsonValue["numThreads"].asUInt()
        };
    }
}
