#include <cassert>

#include "dometer/config/metrics/handler/prometheus_handler_parser.hpp"
#include "dometer/config/metrics/handler/prometheus_transport_parser.hpp"
#include "dometer/metrics/handler/prometheus_options.hpp"
#include "dometer/metrics/handler/prometheus_transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler {
    PrometheusHandlerParser::PrometheusHandlerParser()
        : PrometheusHandlerParser::PrometheusHandlerParser(
                dometer::config::metrics::handler::PrometheusTransportParser()) {}

    PrometheusHandlerParser::PrometheusHandlerParser(
            dometer::config::metrics::handler::PrometheusTransportParser transportParser)
        : transportParser(transportParser) {}

    dometer::metrics::handler::PrometheusOptions PrometheusHandlerParser::fromJson(
            const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("maxTimeSeries"));
        assert(jsonValue["maxTimeSeries"].isUInt());
        assert(jsonValue.isMember("transports"));
        assert(jsonValue["transports"].isArray());

        std::vector<dometer::metrics::handler::PrometheusTransportOptions> transports;
        for(Json::Value::ArrayIndex i = 0; i < jsonValue["transports"].size(); i++) {
            transports.push_back(transportParser.fromJson(jsonValue["transports"][i]));
        }

        return dometer::metrics::handler::PrometheusOptions{
            jsonValue["maxTimeSeries"].asUInt(),
            transports
        };
    }
}
