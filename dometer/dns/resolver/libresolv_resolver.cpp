#include <algorithm>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <errno.h>
#include <iostream>
#include <netdb.h>
#include <resolv.h>
#include <string>

#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/message_factory.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/libresolv_resolver.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace Dns = dometer::dns;
namespace util = dometer::util;
using namespace std::x;

namespace dometer::dns::resolver {
    LibresolvResolver::LibresolvResolver()
        : LibresolvResolver(LibresolvFunction::QUERY) {}

    LibresolvResolver::LibresolvResolver(LibresolvFunction function)
        : function(function) {}

    expected<dns::message::Message, util::Error> LibresolvResolver::resolve(
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
            if(errno > 0) {
                return unexpected<util::Error>(util::Error(
                    "Did not receive a reply",
                    util::Error(strerror(errno), errno))
                );
            }

            // Nasty hack because res_* hides the length of messages from us
            int savedherrno = h_errno;
            for(int i = 0; i <= PACKETSZ; i++) {
                auto reply = dns::message::MessageFactory::makeMessage(buffer, i);
                if(reply) return reply;
            }

            return unexpected<util::Error>(util::Error(
                "Reply was invalid.",
                util::Error(hstrerror(savedherrno), savedherrno))
            );
        }

        return dns::message::MessageFactory::makeMessage(buffer, length);
    }
}
