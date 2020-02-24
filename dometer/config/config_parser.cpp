#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "dometer/config/config.hpp"
#include "dometer/config/config_parser.hpp"
#include "dometer/config/internal_config_parser.hpp"
#include "dometer/config/schema_validator.hpp"
#include "json/json.h"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

using namespace std::x;
namespace util = dometer::util;

namespace dometer::config {
    ConfigParser::ConfigParser()
        : ConfigParser(InternalConfigParser(),
                       SchemaValidator()) {}

    ConfigParser::ConfigParser(InternalConfigParser internalConfigParser,
                               SchemaValidator schemaValidator)
        : internalConfigParser(internalConfigParser),
          schemaValidator(schemaValidator) {}

    expected<Config, util::Error> ConfigParser::fromFile(std::string file) {
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

    expected<Config, util::Error> ConfigParser::fromJson(std::string json) {
        auto validation = schemaValidator.validate(json);
        if(!validation) {
            return unexpected<util::Error>(validation.error());
        } else {
            Json::Value* jsonValue = (*validation).release();
            return internalConfigParser.fromJson(*jsonValue);
        }
    }
}
