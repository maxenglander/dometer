#include "network/dns/answer.h"

namespace DnsTelemeter::Network::Dns {
    Answer::Answer(std::string type, std::string name, std::string content, unsigned int ttl)
    : type(type), name(name), content(content), ttl(ttl) {}
}
