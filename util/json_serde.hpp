#pragma once

#include "json/json.h"
#include "std/experimental/expected.hpp"

using namespace std::experimental;

namespace Dometer::Util {
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
