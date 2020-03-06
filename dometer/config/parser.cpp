#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "dometer/app/options.hpp"
#include "dometer/config/internal_parser.hpp"
#include "dometer/config/parser.hpp"
#include "dometer/config/schema_validator.hpp"
#include "json/json.h"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace app = dometer::app;
namespace util = dometer::util;

namespace dometer::config {
    parser::parser()
        : parser(internal_parser(), schema_validator()) {}

    parser::parser(internal_parser _internal_parser, schema_validator _schema_validator)
        : _internal_parser(_internal_parser),
          _schema_validator(_schema_validator) {}

    std::x::expected<app::options, util::error> parser::from_file(std::string file) {
        std::ifstream ifs(file.c_str());
        if(!ifs.good()) {
            return std::x::unexpected<util::error>(util::error(
                "File does not exist or cannot be read."
            ));
        }

        std::stringstream sstr;
        sstr << ifs.rdbuf();
        return from_json(sstr.str());
    }

    expected<app::options, util::error> parser::from_json(std::string json) {
        auto validation = _schema_validator.validate(json);
        if(!validation) {
            return unexpected<util::error>(util::error(
                "Failed to parse config from JSON.",
                validation.error()
            ));
        } else {
            Json::Value* json_value = (*validation).release();
            return _internal_parser.from_json(*json_value);
        }
    }
}