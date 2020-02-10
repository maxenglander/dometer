#include "config/metrics/handler/prometheus/transport/exposer.hpp"
#include "config/metrics/handler/prometheus/transport/exposer_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler::prometheus::transport {
    Exposer ExposerFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("bindAddress"));
        assert(jsonValue["bindAddress"].IsString());
        assert(jsonValue.HasMember("numThreads"));
        assert(jsonValue["numThreads"].IsUint());
        assert(jsonValue.HasMember("metricsPath"));
        assert(jsonValue["metricsPath"].IsString());

        return Exposer{
            jsonValue["bindAddress"].GetString(),
            jsonValue["numThreads"].GetUint(),
            jsonValue["metricsPath"].GetString()
        };
    }
}
