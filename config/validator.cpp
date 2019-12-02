#include "config/validator.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace Dometer::Config {
    void Validator::validate() {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    }
}
