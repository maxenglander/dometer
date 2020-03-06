#pragma once

#include <memory>
#include <string>

#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"
#include "json/json.h"
#include "valijson/schema.hpp"
#include "valijson/validation_results.hpp"
#include "valijson/validator.hpp"

namespace dometer::config {
    class SchemaValidator {
        public:
            SchemaValidator();
            SchemaValidator(valijson::Validator);
            std::x::expected<std::unique_ptr<Json::Value>, util::error> validate(std::string);
        private:
            util::error makeerror(valijson::ValidationResults);
            static std::unique_ptr<valijson::Schema> getSchema();
            std::x::expected<std::unique_ptr<Json::Value>, util::error> parse(std::string);
            std::x::expected<void, util::error> validate(const valijson::Schema&, const Json::Value&);
            valijson::Validator validator;
    };
}
