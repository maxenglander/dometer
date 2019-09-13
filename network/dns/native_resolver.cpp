#include <algorithm>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <netdb.h>
#include <resolv.h>
#include <string>

#include "experimental/expected.hpp"
#include "network/dns/native_resolver.hpp"
#include "util/error.hpp"

using namespace std::experimental;

namespace Dometer::Network::Dns {
    expected<Packet, Error> NativeResolver::resolve(Packet& query) {
        unsigned char buffer[PACKETSZ];
        size_t length;

        auto question = query.question();

        if(!question)
            return unexpected<Error>(question.error());

        if((length = res_search(question->qname.c_str(), question->qclass,
                        question->qtype, buffer, PACKETSZ)) < 0) {
            return unexpected<Error>(Error{hstrerror(h_errno), h_errno});
        }

        uint16_t id = query.header.id;

        buffer[0] = id >> 8;
        buffer[1] = id & 0xFF;

        return Packet::makePacket(buffer, length);
    }
}
