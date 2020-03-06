#include <cassert>
#include <string>

#include "dometer/config/metrics/handler/prometheus/pull_transport_parser.hpp"
#include "dometer/config/metrics/handler/prometheus/transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    TransportParser::TransportParser()
        : TransportParser(dometer::config::metrics::handler::prometheus::PullTransportParser()) {}

    TransportParser::TransportParser(dometer::config::metrics::handler::prometheus::PullTransportParser pullTransportParser)
        : pullTransportParser(pullTransportParser) {}

    dometer::metrics::handler::prometheus::TransportOptions TransportParser::fromJson(
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
