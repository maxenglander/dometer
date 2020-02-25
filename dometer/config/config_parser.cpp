#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "dometer/app/options.hpp"
#include "dometer/config/config_parser.hpp"
#include "dometer/config/internal_config_parser.hpp"
#include "dometer/config/schema_validator.hpp"
#include "json/json.h"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace app = dometer::app;
namespace util = dometer::util;

namespace dometer::config {
    ConfigParser::ConfigParser()
        : ConfigParser(InternalConfigParser(), SchemaValidator()) {}

    ConfigParser::ConfigParser(InternalConfigParser internalConfigParser, SchemaValidator schemaValidator)
        : internalConfigParser(internalConfigParser),
          schemaValidator(schemaValidator) {}

    std::x::expected<app::Options, util::Error> ConfigParser::fromFile(std::string file) {
        std::ifstream ifs(file.c_str());
        if(!ifs.good()) {
            return std::x::unexpected<util::Error>(util::Error(
                "File does not exist or cannot be read."
            ));
        }

        std::stringstream sstr;
        sstr << ifs.rdbuf();
        return fromJson(sstr.str());
    }

    expected<app::Options, util::Error> ConfigParser::fromJson(std::string json) {
        auto validation = schemaValidator.validate(json);
        if(!validation) {
            return unexpected<util::Error>(validation.error());
        } else {
            Json::Value* jsonValue = (*validation).release();
            return internalConfigParser.fromJson(*jsonValue);
        }
    }
}
