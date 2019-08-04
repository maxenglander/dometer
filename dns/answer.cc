#include "dns/answer.h"

namespace DnsTelemeter {
    namespace Dns {
        Answer::Answer(std::string type, std::string name, std::string content, int ttl) {
            this->type = type;
            this->name = name;
            this->content = content;
            this->ttl = ttl;
        }
    }
}
