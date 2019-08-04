#pragma once

#include <string>

namespace DnsTelemeter {
    namespace Dns {
        class Answer {
            public:
                Answer(std::string type, std::string name, std::string content, int ttl);
                std::string getType();
                std::string getName();
                std::string getContent();
                int getTtl();
            private:
                std::string type;
                std::string name;
                std::string content;
                int ttl;
        };
    }
}
