#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "dometer/config/config.hpp"
#include "dometer/config/config_parser.hpp"
#include "dometer/config/internal_config_parser.hpp"
#include "dometer/config/schema_validator.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
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
        std::cout << "parsing config from file" << std::endl;
        std::ifstream ifs(file.c_str());
        std::stringstream sstr;
        sstr << ifs.rdbuf();
        std::cout << sstr.str() << std::endl;
        return fromJson(sstr.str());
    }

    expected<Config, util::Error> ConfigParser::fromJson(std::string json) {
        auto validation = schemaValidator.validate(json);
        if(!validation) {
            return unexpected<util::Error>(validation.error());
        } else {
            rapidjson::Value* jsonValue = (*validation).release();
            return internalConfigParser.fromJson(*jsonValue);
        }
    }
}
