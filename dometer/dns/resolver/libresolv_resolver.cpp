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
        : LibresolvResolver(libresolv_function::QUERY) {}

    LibresolvResolver::LibresolvResolver(libresolv_function function)
        : function(function) {}

    expected<std::vector<uint8_t>, error> LibresolvResolver::resolve(
        const std::string& qname, const class_& qclass, const type& qtype
    ) const {
        unsigned char buffer[PACKETSZ];
        memset(buffer, 0, PACKETSZ);

        int length;
        if(function == libresolv_function::QUERY) {
            length = res_query(qname.c_str(), qclass, qtype, buffer, PACKETSZ);
        } else {
            length = res_search(qname.c_str(), qclass, qtype, buffer, PACKETSZ);
        }

        if(length > PACKETSZ) {
            return unexpected<error>(error(
                "Reply is too big.",
                errorCode::MSGSIZE
            ));
        }

        if(length >= 0) {
            return std::vector<uint8_t>(buffer, buffer + length);
        }

        if(length < 0 && errno > 0) {
            switch(errno) {
                case ETIMEDOUT:
                    return unexpected<error>(error(
                        "Timed out waiting for reply.",
                        errorCode::TIMEDOUT,
                        dometer::util::error(strerror(errno), errno))
                    );
                default:
                    return unexpected<error>(error(
                        "Did not receive a reply.",
                        errorCode::OTHER,
                        dometer::util::error(strerror(errno), errno))
                    );
            }
        }

        // Nasty hack because res_* hides the length of messages from us
        int savedherrno = h_errno;
        for(int i = 0; i <= PACKETSZ; i++) {
            auto reply = dns::message::parser::parse(buffer, i);
            if(reply) {
                return std::vector<uint8_t>(buffer, buffer + i);
            }
        }

        return unexpected<error>(error(
            "Reply was invalid.",
            errorCode::OTHER,
            dometer::util::error(hstrerror(savedherrno), savedherrno)
        ));
    }
}
