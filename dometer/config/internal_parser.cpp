#include <cassert>
#include <memory>

#include "dometer/app/options.hpp"
#include "dometer/config/internal_parser.hpp"
#include "dometer/util/error.hpp"
#include "json/json.h"
#include "std/x/expected.hpp"

namespace app = dometer::app;
namespace util = dometer::util;

namespace dometer::config {
    internal_parser::internal_parser()
        : internal_parser(dometer::config::dns::parser(),
                       dometer::config::metrics::parser()) {}

    internal_parser::internal_parser(dometer::config::dns::parser dns_parser,
                               dometer::config::metrics::parser metrics_parser)
        : dns_parser(dns_parser),
          metrics_parser(metrics_parser) {}

    app::options internal_parser::from_json(const Json::Value& json_value) const {
        assert(json_value.isMember("dns"));
        assert(json_value["dns"].isObject());
        assert(json_value.isMember("metrics"));
        assert(json_value["metrics"].isObject());
        return app::options{
            dns_parser.from_json(json_value["dns"]),
            metrics_parser.from_json(json_value["metrics"])
        };
    }
}
