#include <assert.h>
#include <deque>
#include <iostream>
#include <string>

#include "config/schema.hpp"
#include "config/validator.hpp"

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
    expected<void, util::Error> Validator::validate(std::string input) {
        rapidjson::Document schemaDocument;

        // Failure interpret the Dometer JSON schema as a JSON document
        // indicates either a bug with RapidJSON or (more likely) a
        // improperly defined JSON document.
        assert(!schemaDocument.Parse(SCHEMA).HasParseError());

        valijson::Schema schema;
        valijson::SchemaParser schemaParser;
        valijson::adapters::RapidJsonAdapter schemaDocumentAdapter(schemaDocument);

        try {
            schemaParser.populateSchema(schemaDocumentAdapter, schema);
        } catch(std::exception &e) {
            // Failure to interpret the Dometer JSON schema as a
            // JSON Schema v4 document indivates either a bug with
            // Valijson or (more likely) an improperly defined JSON schema.
            assert(0);
        }

        rapidjson::Document targetDocument;
        rapidjson::ParseResult targetDocumentParseResult = targetDocument.Parse(input.c_str());
        if(!targetDocumentParseResult) {
            return unexpected<util::Error>(util::Error{
                rapidjson::GetParseError_En(targetDocumentParseResult.Code()),
                targetDocumentParseResult.Code()
            });
        }

        valijson::Validator validator(valijson::Validator::kWeakTypes);
        valijson::ValidationResults validationResults;
        valijson::adapters::RapidJsonAdapter targetDocumentAdapter(targetDocument);
        if(validator.validate(schema, targetDocumentAdapter, &validationResults)) {
            return {};
        }

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

        return unexpected<util::Error>(util::Error{ errorMessage });
    }
}
