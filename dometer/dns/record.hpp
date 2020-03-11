#include "dometer/dns/type.hpp"

namespace dometer::dns {
    struct Record {
        std::string name;
        Type type;
        std::string data;
    };
}
