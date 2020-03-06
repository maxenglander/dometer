#include <cassert>

#include "dometer/config/metrics/handler/prometheus/parser.hpp"
#include "dometer/config/metrics/handler/prometheus/transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/options.hpp"
#include "dometer/metrics/handler/prometheus/transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    parser::parser()
        : parser::parser(transport_parser()) {}

    parser::parser(transport_parser _transport_parser)
        : _transport_parser(_transport_parser) {}

    dometer::metrics::handler::prometheus::options parser::from_json(
            const Json::Value& json_value) const {
        assert(json_value.isMember("maxTimeSeries"));
        assert(json_value["maxTimeSeries"].isUInt());
        assert(json_value.isMember("transports"));
        assert(json_value["transports"].isArray());

        std::vector<dometer::metrics::handler::prometheus::transport_options> transports;
        for(Json::Value::ArrayIndex i = 0; i < json_value["transports"].size(); i++) {
            transports.push_back(_transport_parser.from_json(json_value["transports"][i]));
        }

        return dometer::metrics::handler::prometheus::options{
            json_value["maxTimeSeries"].asUInt(),
            transports
        };
    }
}
