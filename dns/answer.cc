#include "dns/answer.h"

namespace DnsTelemeter::Dns {
    Answer::Answer(std::string type, std::string name, std::string content, unsigned int ttl) {
        this->type = type;
        this->name = name;
        this->content = content;
        this->ttl = ttl;
    }

    std::string Answer::getType() {
        return this->type;
    }

    std::string Answer::getName() {
        return this->name;
    }

    std::string Answer::getContent() {
        return this->content;
    }

    unsigned int Answer::getTtl() {
        return this->ttl;
    }
}
