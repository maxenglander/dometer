#include "config/metrics/handler/prometheus_pull_transport_factory.hpp"
#include "metrics/prometheus_pull_transport_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    dometer::metrics::PrometheusPullTransportOptions PrometheusPullTransportFactory::fromJson(
            const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("bindAddress"));
        assert(jsonValue["bindAddress"].IsString());
        assert(jsonValue.HasMember("numThreads"));
        assert(jsonValue["numThreads"].IsUint());
        assert(jsonValue.HasMember("metricsPath"));
        assert(jsonValue["metricsPath"].IsString());

        return dometer::metrics::PrometheusPullTransportOptions{
            jsonValue["bindAddress"].GetString(),
            jsonValue["metricsPath"].GetString(),
            jsonValue["numThreads"].GetUint()
        };
    }
}
