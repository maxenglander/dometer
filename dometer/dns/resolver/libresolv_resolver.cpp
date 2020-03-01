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

#include "dometer/dns/message/factory.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/resolver/error_code.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/libresolv_resolver.hpp"
#include "std/x/expected.hpp"

namespace Dns = dometer::dns;
using namespace std::x;

namespace dometer::dns::resolver {
    LibresolvResolver::LibresolvResolver()
        : LibresolvResolver(LibresolvFunction::QUERY) {}

    LibresolvResolver::LibresolvResolver(LibresolvFunction function)
        : function(function) {}

    expected<dns::message::Message, Error> LibresolvResolver::resolve(
            const std::string& qname, const Class& qclass, const Type& qtype) const {
        unsigned char buffer[PACKETSZ];
        memset(buffer, 0, PACKETSZ);

        int length;
        if(function == LibresolvFunction::QUERY) {
            length = res_query(qname.c_str(), qclass, qtype, buffer, PACKETSZ);
        } else {
            length = res_search(qname.c_str(), qclass, qtype, buffer, PACKETSZ);
        }

        if(length > PACKETSZ) {
            return unexpected<Error>(Error(
                "Reply is too big.",
                ErrorCode::MSGSIZE
            ));
        }

        if(length < 0 && errno > 0) {
            switch(errno) {
                case ETIMEDOUT:
                    return unexpected<Error>(Error(
                        "Timed out waiting for reply.",
                        ErrorCode::TIMEDOUT,
                        dometer::util::Error(strerror(errno), errno))
                    );
                default:
                    return unexpected<Error>(Error(
                        "Did not receive a reply.",
                        ErrorCode::OTHER,
                        dometer::util::Error(strerror(errno), errno))
                    );
            }
        }

        if(length < 0) {
            // Nasty hack because res_* hides the length of messages from us
            int savedherrno = h_errno;
            for(int i = 0; i <= PACKETSZ; i++) {
                auto reply = dns::message::Parser::parse(buffer, i);
                if(reply) {
                    return *reply;
                }
            }

            return unexpected<Error>(Error(
                "Reply was invalid.",
                ErrorCode::OTHER,
                dometer::util::Error(hstrerror(savedherrno), savedherrno)
            ));
        }

        auto reply = dns::message::Parser::parse(buffer, length);

        if(reply) {
            return *reply;
        } else {
            return unexpected<Error>(Error(
                "Failed to parse reply",
                ErrorCode::PARSEERROR,
                reply.error()
            ));
        }
    }
}
