#pragma once

#include <string>

namespace DnsTelemeter::Network::Dns {
    class Answer {
        public:
            Answer(std::string type, std::string name, std::string content, unsigned int ttl);
            const std::string type;
            const std::string name;
            const std::string content;
            const unsigned int ttl;
    };
}
