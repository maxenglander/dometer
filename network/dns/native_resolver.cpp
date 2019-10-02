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

    expected<Packet, Error> NativeResolver::resolve(Packet& query) const {
        unsigned char buffer[PACKETSZ];
        int length;

        auto question = query.question();

        if(!question)
            return unexpected<Error>(question.error());

        if(resolutionMode == ResolutionMode::QUERY) {
            length = res_query(question->qname.c_str(), question->qclass,
                    question->qtype, buffer, PACKETSZ);
        } else {
            length = res_search(question->qname.c_str(), question->qclass,
                    question->qtype, buffer, PACKETSZ);
        }

        if(length < 0)
            return unexpected<Error>(Error{hstrerror(h_errno), h_errno});

        expected<Packet, Error> reply = Packet::makePacket(buffer, length);
        if(reply) {
            reply->setId(query.id());
        }

        return reply;
    }
}
