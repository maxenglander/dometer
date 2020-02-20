#pragma once

#include <memory>
#include <string>

#include "config/config.hpp"
#include "config/internal_config_parser.hpp"
#include "config/schema_validator.hpp"
#include "rapidjson/document.h"
#include "util/error.hpp"
#include "x/expected.hpp"

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
