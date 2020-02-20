#include "config/metrics/handler/prometheus_handler_parser.hpp"
#include "config/metrics/handler/prometheus_transport_parser.hpp"
#include "metrics/handler/prometheus_options.hpp"
#include "metrics/handler/prometheus_transport_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    PrometheusHandlerParser::PrometheusHandlerParser()
        : PrometheusHandlerParser::PrometheusHandlerParser(
                dometer::config::metrics::handler::PrometheusTransportParser()) {}

    PrometheusHandlerParser::PrometheusHandlerParser(
            dometer::config::metrics::handler::PrometheusTransportParser transportParser)
        : transportParser(transportParser) {}

    dometer::metrics::handler::PrometheusOptions PrometheusHandlerParser::fromJson(
            const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("maxTimeSeries"));
        assert(jsonValue["maxTimeSeries"].IsUint());
        assert(jsonValue.HasMember("transports"));
        assert(jsonValue["transports"].IsArray());

        std::vector<dometer::metrics::handler::PrometheusTransportOptions> transports;
        for(rapidjson::SizeType i = 0; i < jsonValue["transports"].Size(); i++) {
            transports.push_back(transportParser.fromJson(jsonValue["transports"][i]));
        }

        return dometer::metrics::handler::PrometheusOptions{
            jsonValue["maxTimeSeries"].GetUint(),
            transports
        };
    }
}
