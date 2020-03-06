#include <cassert>

#include "dometer/config/metrics/handler/prometheus/pull_transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/pull_transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    dometer::metrics::handler::prometheus::pull_transport_options pull_transport_parser::from_json(
            const Json::Value& json_value) const {
        assert(json_value.isMember("bindAddress"));
        assert(json_value["bindAddress"].isString());
        assert(json_value.isMember("numThreads"));
        assert(json_value["numThreads"].isUInt());
        assert(json_value.isMember("metricsPath"));
        assert(json_value["metricsPath"].isString());

        return dometer::metrics::handler::prometheus::pull_transport_options{
            json_value["bindAddress"].asString(),
            json_value["metricsPath"].asString(),
            json_value["numThreads"].asUInt()
        };
    }
}
