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
        : parser(InternalParser(), SchemaValidator()) {}

    parser::parser(InternalParser internalParser, SchemaValidator schemaValidator)
        : internalParser(internalParser),
          schemaValidator(schemaValidator) {}

    std::x::expected<app::options, util::error> parser::fromFile(std::string file) {
        std::ifstream ifs(file.c_str());
        if(!ifs.good()) {
            return std::x::unexpected<util::error>(util::error(
                "File does not exist or cannot be read."
            ));
        }

        std::stringstream sstr;
        sstr << ifs.rdbuf();
        return fromJson(sstr.str());
    }

    expected<app::options, util::error> parser::fromJson(std::string json) {
        auto validation = schemaValidator.validate(json);
        if(!validation) {
            return unexpected<util::error>(util::error(
                "Failed to parse config from JSON.",
                validation.error()
            ));
        } else {
            Json::Value* jsonValue = (*validation).release();
            return internalParser.fromJson(*jsonValue);
        }
    }
}
