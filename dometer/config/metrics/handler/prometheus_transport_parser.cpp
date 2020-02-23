#include <cassert>
#include <string>

#include "dometer/config/metrics/handler/prometheus_pull_transport_parser.hpp"
#include "dometer/config/metrics/handler/prometheus_transport_parser.hpp"
#include "dometer/metrics/handler/prometheus_transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler {
    PrometheusTransportParser::PrometheusTransportParser()
        : PrometheusTransportParser(dometer::config::metrics::handler::PrometheusPullTransportParser()) {}

    PrometheusTransportParser::PrometheusTransportParser(
            dometer::config::metrics::handler::PrometheusPullTransportParser pullTransportParser)
        : pullTransportParser(pullTransportParser) {}

    dometer::metrics::handler::PrometheusTransportOptions PrometheusTransportParser::fromJson(
            const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("type"));
        assert(jsonValue["type"].isString());

        std::string type = jsonValue["type"].asString();
        if(type == "pull") {
            assert(jsonValue.isMember("exposer"));
            assert(jsonValue["exposer"].isObject());

            return pullTransportParser.fromJson(jsonValue["exposer"]);
        } else {
            assert(false);
        }
    }
}
