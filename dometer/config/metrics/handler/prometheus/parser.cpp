#include <cassert>

#include "dometer/config/metrics/handler/prometheus/parser.hpp"
#include "dometer/config/metrics/handler/prometheus/transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/options.hpp"
#include "dometer/metrics/handler/prometheus/transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    parser::parser()
        : parser::parser(dometer::config::metrics::handler::prometheus::TransportParser()) {}

    parser::parser(
            dometer::config::metrics::handler::prometheus::TransportParser transportParser)
        : transportParser(transportParser) {}

    dometer::metrics::handler::prometheus::options parser::fromJson(
            const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("maxTimeSeries"));
        assert(jsonValue["maxTimeSeries"].isUInt());
        assert(jsonValue.isMember("transports"));
        assert(jsonValue["transports"].isArray());

        std::vector<dometer::metrics::handler::prometheus::TransportOptions> transports;
        for(Json::Value::ArrayIndex i = 0; i < jsonValue["transports"].size(); i++) {
            transports.push_back(transportParser.fromJson(jsonValue["transports"][i]));
        }

        return dometer::metrics::handler::prometheus::options{
            jsonValue["maxTimeSeries"].asUInt(),
            transports
        };
    }
}
