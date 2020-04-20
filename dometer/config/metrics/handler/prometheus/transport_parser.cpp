#include <cassert>
#include <string>

#include "dometer/config/metrics/handler/prometheus/pull_transport_parser.hpp"
#include "dometer/config/metrics/handler/prometheus/transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    transport_parser::transport_parser()
        : transport_parser(dometer::config::metrics::handler::prometheus::pull_transport_parser()) {}

    transport_parser::transport_parser(dometer::config::metrics::handler::prometheus::pull_transport_parser pull_transport_parser)
        : pull_transport_parser(pull_transport_parser) {}

    dometer::metrics::handler::prometheus::transport_options transport_parser::from_json(
            const Json::Value& json_value) const {
        assert(json_value.isMember("type"));
        assert(json_value["type"].isString());

        std::string type = json_value["type"].asString();
        if(type == "pull") {
            assert(json_value.isMember("exposer"));
            assert(json_value["exposer"].isObject());

            return pull_transport_parser.from_json(json_value["exposer"]);
        } else {
            assert(false);
        }
    }
}
