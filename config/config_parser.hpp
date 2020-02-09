#pragma once

#include <memory>
#include <string>

#include "config/config.hpp"
#include "config/config_factory.hpp"
#include "config/schema_validator.hpp"
#include "experimental/expected.hpp"
#include "rapidjson/document.h"
#include "util/error.hpp"

using namespace std::experimental;
namespace util = dometer::util;

namespace dometer::config {
    class ConfigParser {
        public:
            ConfigParser();
            ConfigParser(ConfigFactory, SchemaValidator);
            expected<Config, util::Error> parse(std::string);
        private:
            const ConfigFactory configFactory;
            SchemaValidator schemaValidator;
    };
}
