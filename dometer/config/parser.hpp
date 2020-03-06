#pragma once

#include <memory>
#include <string>

#include "dometer/app/options.hpp"
#include "dometer/config/internal_parser.hpp"
#include "dometer/config/schema_validator.hpp"
#include "json/json.h"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace app = dometer::app;
namespace util = dometer::util;

namespace dometer::config {
    class parser {
        public:
            parser();
            parser(InternalParser, SchemaValidator);
            std::x::expected<app::options, util::error> fromFile(std::string);
            std::x::expected<app::options, util::error> fromJson(std::string);
        private:
            InternalParser internalParser;
            SchemaValidator schemaValidator;
    };
}
