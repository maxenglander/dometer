#pragma once

#include <memory>
#include <string>

#include "x/expected.hpp"
#include "rapidjson/document.h"
#include "valijson/schema.hpp"
#include "valijson/validation_results.hpp"
#include "valijson/validator.hpp"
#include "util/error.hpp"

using namespace std::x;

namespace dometer::config {
    class SchemaValidator {
        public:
            SchemaValidator();
            SchemaValidator(valijson::Validator);
            expected<std::unique_ptr<rapidjson::Value>, util::Error> validate(std::string);
        private:
            util::Error makeError(valijson::ValidationResults);
            static std::unique_ptr<valijson::Schema> getSchema();
            expected<std::unique_ptr<rapidjson::Document>, util::Error> parse(std::string);
            expected<void, util::Error> validate(const valijson::Schema&, const rapidjson::Document&);
            valijson::Validator validator;
    };
}
