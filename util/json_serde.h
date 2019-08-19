#pragma once

#include "json/json.h"
#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::Util {
    class JsonSerde {
        public:
            JsonSerde();
            expected<Json::Value, std::string> deserialize(std::string);
            std::string serialize(Json::Value);
        private:
            Json::CharReader* reader;
            Json::StreamWriter* writer;
    };
}