#include <memory>

#include "config/config.hpp"
#include "config/config_parser.hpp"
#include "config/internal_config_parser.hpp"
#include "config/schema_validator.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "util/error.hpp"
#include "x/expected.hpp"

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
