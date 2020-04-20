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
    schema_validator::schema_validator()
        : schema_validator::schema_validator(valijson::Validator(valijson::Validator::kWeakTypes)) {}

    schema_validator::schema_validator(valijson::Validator validator) : validator(validator) {}

    util::error schema_validator::make_error(valijson::ValidationResults validation_results) {
        std::vector<std::string> details;
        for(auto it = validation_results.begin(); it != validation_results.end(); it++) {
            valijson::ValidationResults::Error error = *it;

            std::string context;
            std::vector<std::string>::iterator context_it = error.context.begin();
            for(; context_it != error.context.end(); context_it++) {
                context += *context_it;
            }

            details.insert(details.begin(), context + ": " + error.description);
        }

        return util::error("Failed to validate configuration against schema.", details);
    }

    std::unique_ptr<valijson::Schema> schema_validator::get_schema() {
        std::string errs;
        Json::Value root;

        Json::CharReaderBuilder rbuilder;
        std::unique_ptr<Json::CharReader> const reader(rbuilder.newCharReader());

        // Failure interpret the dometer JSON schema as a JSON document
        // indicates either a bug with RapidJSON or (more likely) a
        // improperly defined JSON document.
        assert(reader->parse(&SCHEMA[0], &SCHEMA[SCHEMA.size() - 1], &root, &errs));

        auto schema = std::x::make_unique<valijson::Schema>();
        valijson::SchemaParser schema_parser;
        valijson::adapters::JsonCppAdapter schema_document_adapter(root);

        try {
            schema_parser.populateSchema(schema_document_adapter, *schema);
        } catch(std::exception &e) {
            // Failure to interpret the dometer JSON schema as a
            // JSON Schema v4 document indivates either a bug with
            // Valijson or (more likely) an improperly defined JSON schema.
            assert(0);
        }

        return std::move(schema);
    }

    std::x::expected<std::unique_ptr<Json::Value>, util::error> schema_validator::parse(std::string input) {
        std::string errs;
        auto root = std::x::make_unique<Json::Value>();

        Json::CharReaderBuilder rbuilder;
        std::unique_ptr<Json::CharReader> const reader(rbuilder.newCharReader());

        if(!reader->parse(&input[0], &input[input.size() - 1], &(*root), &errs)) {
            return std::x::unexpected<util::error>(util::error(
                "Failed to parse JSON.",
                util::string_helper::split('\n', errs)
            ));
        }

        return std::move(root);
    }

    std::x::expected<std::unique_ptr<Json::Value>, util::error> schema_validator::validate(std::string input) {
        std::unique_ptr<valijson::Schema> schema = this->get_schema();

        auto parse_result = parse(input);
        if(!parse_result) {
            return std::x::unexpected<util::error>(util::error(
                "Failed to parse JSON.",
                parse_result.error()
            ));
        }

        std::unique_ptr<Json::Value> root = std::move(*parse_result);

        auto validation_result = validate(*(schema.get()), *(root.get()));
        if(!validation_result) {
            return std::x::unexpected<util::error>(util::error(
                "Failed to validate JSON.",
                validation_result.error()
            ));
        }

        return std::move(root);
    }

    std::x::expected<void, util::error> schema_validator::validate(const valijson::Schema& schema, const Json::Value& root) {
        valijson::ValidationResults validation_results;
        valijson::adapters::JsonCppAdapter value_adapter(root);
        if(!validator.validate(schema, value_adapter, &validation_results)) {
            return std::x::unexpected<util::error>(make_error(validation_results));
        }
        return {};
    }
}
