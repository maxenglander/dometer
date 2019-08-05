#include <string>

#include "dns/query.h"

namespace DnsTelemeter::Dns {
    Query::Query(std::string type, std::string name) {
        this->type = type;
        this->name = name;
    }
}
