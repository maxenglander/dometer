#pragma once

#include <string>

namespace DnsTelemeter {
    namespace Dns {
        class Query {
            public:
                Query(std::string type, std::string name);
                std::string getType();
                std::string getName();
            private:
                std::string type;
                std::string name;
        };
    }
}
