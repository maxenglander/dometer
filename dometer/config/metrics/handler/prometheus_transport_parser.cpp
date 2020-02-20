#include <string>

#include "dometer/config/metrics/handler/prometheus_pull_transport_parser.hpp"
#include "dometer/config/metrics/handler/prometheus_transport_parser.hpp"
#include "dometer/metrics/handler/prometheus_transport_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    PrometheusTransportParser::PrometheusTransportParser()
        : PrometheusTransportParser(dometer::config::metrics::handler::PrometheusPullTransportParser()) {}

    PrometheusTransportParser::PrometheusTransportParser(
            dometer::config::metrics::handler::PrometheusPullTransportParser pullTransportParser)
        : pullTransportParser(pullTransportParser) {}

    dometer::metrics::handler::PrometheusTransportOptions PrometheusTransportParser::fromJson(
            const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("type"));
        assert(jsonValue["type"].IsString());

        std::string type = jsonValue["type"].GetString();
        if(type == "pull") {
            assert(jsonValue.HasMember("exposer"));
            assert(jsonValue["exposer"].IsObject());

            return pullTransportParser.fromJson(jsonValue["exposer"]);
        } else {
            assert(false);
        }
    }
}
