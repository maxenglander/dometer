#include <assert.h>
#include <deque>
#include <iostream>
#include <memory>
#include <string>

#include "config/schema.hpp"
#include "config/schema_validator.hpp"
#include "experimental/expected.hpp"
#include "rapidjson/error/en.h"
#include "rapidjson/schema.h"
#include "rapidjson/stringbuffer.h"
#include "valijson/adapters/rapidjson_adapter.hpp"
#include "valijson/utils/rapidjson_utils.hpp"
#include "valijson/schema.hpp"
#include "valijson/schema_parser.hpp"
#include "valijson/validation_results.hpp"
#include "valijson/validator.hpp"
#include "util/error.hpp"

using namespace std::experimental;

namespace dometer::config {
    SchemaValidator::SchemaValidator()
        : SchemaValidator::SchemaValidator(valijson::Validator(valijson::Validator::kWeakTypes)) {}

    SchemaValidator::SchemaValidator(valijson::Validator validator) : validator(validator) {}

    util::Error SchemaValidator::makeError(valijson::ValidationResults validationResults) {
        std::string errorMessage;
        unsigned int errorIndex = validationResults.numErrors() - 1;
        std::deque<valijson::ValidationResults::Error>::const_iterator errorIt = validationResults.begin();
        for(; errorIt != validationResults.end(); errorIt++) {
            valijson::ValidationResults::Error error = *errorIt;

            std::string context;
            std::vector<std::string>::iterator contextIt = error.context.begin();
            for(; contextIt != error.context.end(); contextIt++) {
                context += *contextIt;
            }

            if(errorIndex < validationResults.numErrors() - 1) {
                errorMessage = "\n" + errorMessage;
            }
            errorMessage = "@" + context + ": " + error.description
                         + errorMessage;
            errorIndex--;
        }

        return util::Error{ errorMessage };
    }

    std::unique_ptr<valijson::Schema> SchemaValidator::getSchema() {
        rapidjson::Document schemaDocument;

        // Failure interpret the Dometer JSON schema as a JSON document
        // indicates either a bug with RapidJSON or (more likely) a
        // improperly defined JSON document.
        assert(!schemaDocument.Parse(SCHEMA).HasParseError());

        auto schema = std::make_unique<valijson::Schema>();
        valijson::SchemaParser schemaParser;
        valijson::adapters::RapidJsonAdapter schemaDocumentAdapter(schemaDocument);

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

    expected<std::unique_ptr<rapidjson::Document>, util::Error> SchemaValidator::parse(std::string input) {
        auto document = std::make_unique<rapidjson::Document>();
        rapidjson::ParseResult result = document->Parse(input.c_str());
        if(!result) {
            return unexpected<util::Error>(util::Error{
                rapidjson::GetParseError_En(result.Code()),
                result.Code()
            });
        }

        return std::move(document);
    }

    expected<std::unique_ptr<rapidjson::Value>, util::Error> SchemaValidator::validate(std::string input) {
        std::unique_ptr<valijson::Schema> schema = this->getSchema();

        auto parseResult = parse(input);
        if(!parseResult) {
            return unexpected<util::Error>(parseResult.error());
        }

        std::unique_ptr<rapidjson::Document> document = std::move(*parseResult);

        auto validationResult = validate(*(schema.get()), *(document.get()));
        if(!validationResult) {
            return unexpected<util::Error>(validationResult.error());
        }

        return std::move(document);
    }

    expected<void, util::Error> SchemaValidator::validate(const valijson::Schema& schema, const rapidjson::Document& document) {
        valijson::ValidationResults validationResults;
        valijson::adapters::RapidJsonAdapter documentAdapter(document);
        if(!validator.validate(schema, documentAdapter, &validationResults)) {
            return unexpected<util::Error>(makeError(validationResults));
        }
        return {};
    }
}
