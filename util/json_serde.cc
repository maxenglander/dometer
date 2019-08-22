#include <iostream>
#include <sstream>
#include <string>

#include "json/json.h"
#include "std/experimental/expected.h"
#include "util/json_serde.h"

using namespace std::experimental;

namespace DnsTelemeter::Util {
    JsonSerde::JsonSerde() {
        Json::CharReaderBuilder readerBuilder;
        reader = readerBuilder.newCharReader();
        Json::StreamWriterBuilder writerBuilder;
        writerBuilder["indentation"] = "";
        writer = writerBuilder.newStreamWriter();
    }

    expected<Json::Value, std::string> JsonSerde::deserialize(std::string value) {
        Json::Value out;
        std::string errors;
        if(reader->parse(value.data(), value.data() + value.size(), &out, &errors)) {
            return out;
        }
        return unexpected<std::string>(std::string("Failed to parse value (" + value + ") as JSON: " + errors));
    }

    std::string JsonSerde::serialize(Json::Value in) {
        std::stringbuf buffer;
        std::ostream   stream(&buffer);
        writer->write(in, &stream);
        return buffer.str();
    }
}
