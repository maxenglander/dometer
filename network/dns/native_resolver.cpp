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
#include "network/dns/resolution_mode.hpp"
#include "util/error.hpp"

using namespace std::experimental;

namespace Dometer::Network::Dns {
    NativeResolver::NativeResolver()
        : NativeResolver(ResolutionMode::QUERY) {}

    NativeResolver::NativeResolver(ResolutionMode resolutionMode)
        : resolutionMode(resolutionMode) {}

    expected<Packet, Error> NativeResolver::resolve(Packet& query) {
        unsigned char buffer[PACKETSZ];
        size_t length;

        auto question = query.question();

        if(!question)
            return unexpected<Error>(question.error());

        if(resolutionMode == ResolutionMode::QUERY) {
            if((length = res_query(question->qname.c_str(), question->qclass,
                            question->qtype, buffer, PACKETSZ)) < 0) {
                return unexpected<Error>(Error{hstrerror(h_errno), h_errno});
            }
        } else {
            if((length = res_search(question->qname.c_str(), question->qclass,
                            question->qtype, buffer, PACKETSZ)) < 0) {
                return unexpected<Error>(Error{hstrerror(h_errno), h_errno});
            }
        }

        uint16_t id = query.id();

        buffer[0] = id >> 8;
        buffer[1] = id & 0xFF;

        return Packet::makePacket(buffer, length);
    }
}
