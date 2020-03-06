#include <cassert>

#include "dometer/config/metrics/handler/prometheus/parser.hpp"
#include "dometer/config/metrics/handler/prometheus/transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/options.hpp"
#include "dometer/metrics/handler/prometheus/transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    Parser::Parser()
        : Parser::Parser(dometer::config::metrics::handler::prometheus::TransportParser()) {}

    Parser::Parser(
            dometer::config::metrics::handler::prometheus::TransportParser transportParser)
        : transportParser(transportParser) {}

    dometer::metrics::handler::prometheus::Options Parser::fromJson(
            const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("maxTimeSeries"));
        assert(jsonValue["maxTimeSeries"].isUInt());
        assert(jsonValue.isMember("transports"));
        assert(jsonValue["transports"].isArray());

        std::vector<dometer::metrics::handler::prometheus::TransportOptions> transports;
        for(Json::Value::ArrayIndex i = 0; i < jsonValue["transports"].size(); i++) {
            transports.push_back(transportParser.fromJson(jsonValue["transports"][i]));
        }

        return dometer::metrics::handler::prometheus::Options{
            jsonValue["maxTimeSeries"].asUInt(),
            transports
        };
    }
}
