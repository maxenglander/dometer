#include <memory>

#include "config/config.hpp"
#include "config/config_factory.hpp"
#include "config/config_parser.hpp"
#include "config/schema_validator.hpp"
#include "experimental/expected.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "util/error.hpp"

using namespace std::experimental;
namespace util = dometer::util;

namespace dometer::config {
    ConfigParser::ConfigParser() : ConfigParser(ConfigFactory(), SchemaValidator()) {}

    ConfigParser::ConfigParser(ConfigFactory configFactory, SchemaValidator schemaValidator)
        : configFactory(configFactory), schemaValidator(schemaValidator) {}

    expected<Config, util::Error> ConfigParser::parse(std::string json) {
        auto validation = schemaValidator.validate(json);
        if(!validation) {
            return unexpected<util::Error>(validation.error());
        } else {
            rapidjson::Value* jsonValue = (*validation).release();
            return configFactory.fromJson(*jsonValue);
        }
    }
}
