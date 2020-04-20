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
    class schema_validator {
        public:
            schema_validator();
            schema_validator(valijson::Validator);
            std::x::expected<std::unique_ptr<Json::Value>, util::error> validate(std::string);
        private:
            util::error make_error(valijson::ValidationResults);
            static std::unique_ptr<valijson::Schema> get_schema();
            std::x::expected<std::unique_ptr<Json::Value>, util::error> parse(std::string);
            std::x::expected<void, util::error> validate(const valijson::Schema&, const Json::Value&);
            valijson::Validator validator;
    };
}
