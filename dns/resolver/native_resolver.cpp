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

#include "dns/packet.hpp"
#include "dns/resolver/native_resolver.hpp"
#include "dns/resolver/resolution_mode.hpp"
#include "experimental/expected.hpp"
#include "util/error.hpp"

namespace Dns = Dometer::Dns;
namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Dns::Resolver {
    NativeResolver::NativeResolver()
        : NativeResolver(ResolutionMode::QUERY) {}

    NativeResolver::NativeResolver(ResolutionMode resolutionMode)
        : resolutionMode(resolutionMode) {}

    expected<Dns::Packet, Util::Error> NativeResolver::resolve(
            const std::string& qname, const Class& qclass, const Type& qtype) const {
        unsigned char buffer[PACKETSZ];
        memset(buffer, 0, PACKETSZ);

        int length;
        if(resolutionMode == ResolutionMode::QUERY) {
            length = res_query(qname.c_str(), qclass, qtype, buffer, PACKETSZ);
        } else {
            length = res_search(qname.c_str(), qclass, qtype, buffer, PACKETSZ);
        }

        if(length < 0) {
            int savedherrno = h_errno;

            // Nasty hack because res_* hides the length of packets from us
            for(int i = 0; i <= PACKETSZ; i++) {
                auto reply = Dns::Packet::makePacket(buffer, i);
                if(reply) return reply;
            }

            return unexpected<Util::Error>(Util::Error{hstrerror(savedherrno), savedherrno});
        }

        return Dns::Packet::makePacket(buffer, length);
    }
}
