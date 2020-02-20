#include "dometer/config/metrics/handler/prometheus_pull_transport_parser.hpp"
#include "dometer/metrics/handler/prometheus_pull_transport_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    dometer::metrics::handler::PrometheusPullTransportOptions PrometheusPullTransportParser::fromJson(
            const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("bindAddress"));
        assert(jsonValue["bindAddress"].IsString());
        assert(jsonValue.HasMember("numThreads"));
        assert(jsonValue["numThreads"].IsUint());
        assert(jsonValue.HasMember("metricsPath"));
        assert(jsonValue["metricsPath"].IsString());

        return dometer::metrics::handler::PrometheusPullTransportOptions{
            jsonValue["bindAddress"].GetString(),
            jsonValue["metricsPath"].GetString(),
            jsonValue["numThreads"].GetUint()
        };
    }
}
