#pragma once

#include <memory>
#include <string>

#include "dometer/config/config.hpp"
#include "dometer/config/internal_config_parser.hpp"
#include "dometer/config/schema_validator.hpp"
#include "json/json.h"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

using namespace std::x;
namespace util = dometer::util;

namespace dometer::config {
    class ConfigParser {
        public:
            ConfigParser();
            ConfigParser(InternalConfigParser,
                         SchemaValidator);
            expected<Config, util::Error> fromFile(std::string);
            expected<Config, util::Error> fromJson(std::string);
        private:
            InternalConfigParser internalConfigParser;
            SchemaValidator schemaValidator;
    };
}
