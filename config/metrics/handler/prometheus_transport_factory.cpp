#include <string>

#include "config/metrics/handler/prometheus_pull_transport_factory.hpp"
#include "config/metrics/handler/prometheus_transport_factory.hpp"
#include "metrics/handler/prometheus_transport_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    PrometheusTransportFactory::PrometheusTransportFactory()
        : PrometheusTransportFactory(dometer::config::metrics::handler::PrometheusPullTransportFactory()) {}

    PrometheusTransportFactory::PrometheusTransportFactory(
            dometer::config::metrics::handler::PrometheusPullTransportFactory pullTransportFactory)
        : pullTransportFactory(pullTransportFactory) {}

    dometer::metrics::handler::PrometheusTransportOptions PrometheusTransportFactory::fromJson(
            const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("type"));
        assert(jsonValue["type"].IsString());

        std::string type = jsonValue["type"].GetString();
        if(type == "pull") {
            assert(jsonValue.HasMember("exposer"));
            assert(jsonValue["exposer"].IsObject());

            return pullTransportFactory.fromJson(jsonValue["exposer"]);
        } else {
            assert(false);
        }
    }
}
