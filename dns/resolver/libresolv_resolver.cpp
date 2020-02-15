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
#include "dns/resolver/libresolv_function.hpp"
#include "dns/resolver/libresolv_resolver.hpp"
#include "x/expected.hpp"
#include "util/error.hpp"

namespace Dns = dometer::dns;
namespace util = dometer::util;
using namespace std::x;

namespace dometer::dns::resolver {
    LibresolvResolver::LibresolvResolver()
        : LibresolvResolver(LibresolvFunction::QUERY) {}

    LibresolvResolver::LibresolvResolver(LibresolvFunction function)
        : function(function) {}

    expected<dns::Packet, util::Error> LibresolvResolver::resolve(
            const std::string& qname, const Class& qclass, const Type& qtype) const {
        unsigned char buffer[PACKETSZ];
        memset(buffer, 0, PACKETSZ);

        int length;
        if(function == LibresolvFunction::QUERY) {
            length = res_query(qname.c_str(), qclass, qtype, buffer, PACKETSZ);
        } else {
            length = res_search(qname.c_str(), qclass, qtype, buffer, PACKETSZ);
        }

        if(length < 0) {
            int savedherrno = h_errno;

            // Nasty hack because res_* hides the length of packets from us
            for(int i = 0; i <= PACKETSZ; i++) {
                auto reply = dns::Packet::makePacket(buffer, i);
                if(reply) return reply;
            }

            return unexpected<util::Error>(util::Error{hstrerror(savedherrno), savedherrno});
        }

        return dns::Packet::makePacket(buffer, length);
    }
}
