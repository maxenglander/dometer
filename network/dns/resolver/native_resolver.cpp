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
#include "network/dns/resolver/native_resolver.hpp"
#include "network/dns/resolver/resolution_mode.hpp"
#include "util/error.hpp"

using namespace Dometer::Network::Dns;
using namespace std::experimental;

namespace Dometer::Network::Dns::Resolver {
    NativeResolver::NativeResolver()
        : NativeResolver(ResolutionMode::QUERY) {}

    NativeResolver::NativeResolver(ResolutionMode resolutionMode)
        : resolutionMode(resolutionMode) {}

    expected<Packet, Error> NativeResolver::resolve(
            const std::string& qname, const Class& qclass, const Type& qtype) const {
        unsigned char buffer[4096];
        int length;

        if(resolutionMode == ResolutionMode::QUERY) {
            length = res_query(qname.c_str(), qclass, qtype, buffer, sizeof(buffer));
        } else {
            length = res_search(qname.c_str(), qclass, qtype, buffer, sizeof(buffer));
        }

        if(length < 0)
            return unexpected<Error>(Error{hstrerror(h_errno), h_errno});

        return Packet::makePacket(buffer, length);
    }
}
