#include <cassert>
#include <deque>
#include <iostream>
#include <memory>
#include <string>

#include "dometer/config/schema.hpp"
#include "dometer/config/schema_validator.hpp"
#include "dometer/util/error.hpp"
#include "dometer/util/string_helper.hpp"
#include "json/json.h"
#include "std/x/expected.hpp"
#include "std/x/unique.hpp"
#include "valijson/adapters/jsoncpp_adapter.hpp"
#include "valijson/schema.hpp"
#include "valijson/schema_parser.hpp"
#include "valijson/validation_results.hpp"
#include "valijson/validator.hpp"

namespace dometer::config {
    SchemaValidator::SchemaValidator()
        : SchemaValidator::SchemaValidator(valijson::Validator(valijson::Validator::kWeakTypes)) {}

    SchemaValidator::SchemaValidator(valijson::Validator validator) : validator(validator) {}

    util::Error SchemaValidator::makeError(valijson::ValidationResults validationResults) {
        std::vector<std::string> details;
        for(auto it = validationResults.begin(); it != validationResults.end(); it++) {
            valijson::ValidationResults::Error error = *it;

            std::string context;
            std::vector<std::string>::iterator contextIt = error.context.begin();
            for(; contextIt != error.context.end(); contextIt++) {
                context += *contextIt;
            }

            details.insert(details.begin(), context + ": " + error.description);
        }

        return util::Error("Failed to validate configuration against schema.", details);
    }

    std::unique_ptr<valijson::Schema> SchemaValidator::getSchema() {
        std::string errs;
        Json::Value root;

        Json::CharReaderBuilder rbuilder;
        std::unique_ptr<Json::CharReader> const reader(rbuilder.newCharReader());

        // Failure interpret the Dometer JSON schema as a JSON document
        // indicates either a bug with RapidJSON or (more likely) a
        // improperly defined JSON document.
        assert(reader->parse(&SCHEMA[0], &SCHEMA[SCHEMA.size() - 1], &root, &errs));

        auto schema = std::x::make_unique<valijson::Schema>();
        valijson::SchemaParser schemaParser;
        valijson::adapters::JsonCppAdapter schemaDocumentAdapter(root);

        try {
            schemaParser.populateSchema(schemaDocumentAdapter, *schema);
        } catch(std::exception &e) {
            // Failure to interpret the Dometer JSON schema as a
            // JSON Schema v4 document indivates either a bug with
            // Valijson or (more likely) an improperly defined JSON schema.
            assert(0);
        }

        return std::move(schema);
    }

    std::x::expected<std::unique_ptr<Json::Value>, util::Error> SchemaValidator::parse(std::string input) {
        std::string errs;
        auto root = std::x::make_unique<Json::Value>();

        Json::CharReaderBuilder rbuilder;
        std::unique_ptr<Json::CharReader> const reader(rbuilder.newCharReader());

        if(!reader->parse(&input[0], &input[input.size() - 1], &(*root), &errs)) {
            return std::x::unexpected<util::Error>(util::Error(
                "Failed to parse JSON.",
                util::StringHelper::split('\n', errs)
            ));
        }

        return std::move(root);
    }

    std::x::expected<std::unique_ptr<Json::Value>, util::Error> SchemaValidator::validate(std::string input) {
        std::unique_ptr<valijson::Schema> schema = this->getSchema();

        auto parseResult = parse(input);
        if(!parseResult) {
            return std::x::unexpected<util::Error>(util::Error(
                "Failed to parse JSON.",
                parseResult.error()
            ));
        }

        std::unique_ptr<Json::Value> root = std::move(*parseResult);

        auto validationResult = validate(*(schema.get()), *(root.get()));
        if(!validationResult) {
            return std::x::unexpected<util::Error>(util::Error(
                "Failed to validate JSON.",
                validationResult.error()
            ));
        }

        return std::move(root);
    }

    std::x::expected<void, util::Error> SchemaValidator::validate(const valijson::Schema& schema, const Json::Value& root) {
        valijson::ValidationResults validationResults;
        valijson::adapters::JsonCppAdapter valueAdapter(root);
        if(!validator.validate(schema, valueAdapter, &validationResults)) {
            return std::x::unexpected<util::Error>(makeError(validationResults));
        }
        return {};
    }
}
