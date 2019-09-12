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

#include "network/dns/answer.hpp"
#include "network/dns/header.hpp"
#include "network/dns/native_resolver.hpp"
#include "std/experimental/expected.hpp"
#include "util/error.hpp"

using namespace std::experimental;

namespace Dometer::Network::Dns {
    expected<Response, Error> NativeResolver::lookup(std::string name, std::string type) {
        std::cerr << "Got a request of type " + type + " for name " + name + "\n";

        if     (type == "A")
            return lookup(name, ns_t_a, &parseARecord);
        else if(type == "SOA")
            return lookup(name, ns_t_soa, &parseSOARecord);

        return unexpected<Error>(Error{"Lookup of type not supported: " + type, 0});
    }

    expected<Response, Error> NativeResolver::lookup(std::string name, ns_type type,
            expected<Answer, Error> (*parser)(ns_msg* handle, ns_rr* rr)) {
        int len;
        unsigned char nsbuf[NS_PACKETSZ];

        /*************************************************/
        /* Perform a DNS lookup using any search domains */
        /* defined in /etc/resolv.conf. See resolv(2).   */
        /*************************************************/
        len = res_search(name.c_str(), C_IN, type, nsbuf, sizeof(nsbuf));
        if(len < 0) {
            return unexpected<Error>(Error{
                std::string(hstrerror(h_errno)),
                h_errno
            });
        }

        /*************************************************/
        /* Parse the DNS response.                       */
        /*************************************************/
        ns_msg handle;
        ns_initparse(nsbuf, len, &handle);

        /*************************************************/
        /* Check for errors.                             */
        /*************************************************/
        int rcode = ns_msg_getflag(handle, ns_f_rcode);
        if(rcode != ns_r_noerror) {
            return Response{
                Header{true, rcode},
                std::vector<Answer>()
            };
        }

        /*************************************************/
        /* Iterate over each answer.                     */
        /*************************************************/
        std::vector<Answer> answers;
        for(int rrnum = 0; rrnum < ns_msg_count(handle, ns_s_an); rrnum++) {
            ns_rr rr;

            /*************************************************/
            /* Parse the answer section into a record.       */
            /*************************************************/
            if(ns_parserr(&handle, ns_s_an, rrnum, &rr) < 0) {
                return unexpected<Error>(Error{
                    std::string(strerror(errno)),
                    errno
                });
            }

            if(ns_rr_type(rr) != type) {
                continue;
            }

            /*************************************************/
            /* Append the IP and TTL to the answers vector.  */
            /*************************************************/
            expected<Answer, Error> answer = (*parser)(&handle, &rr);
            if(!answer) return unexpected<Error>(answer.error());
            answers.push_back(*answer);
        }

        return Response{
            Header{rcode},
            answers
        };
    }

    expected<Answer, Error> NativeResolver::parseARecord(ns_msg* handle, ns_rr* rr) {
        /*************************************************/
        /* Extract the IP address and TTL.               */
        /*************************************************/
        char ip[INET_ADDRSTRLEN];
        u_int32_t ttl;
        inet_ntop(AF_INET, ns_rr_rdata(*rr), ip, INET_ADDRSTRLEN);
        ttl = ns_rr_ttl(*rr);

        return Answer{std::string(ns_rr_name(*rr)), "A", ip, ttl};
    }

    expected<Answer, Error> NativeResolver::parseSOARecord(ns_msg* handle, ns_rr* rr) {
        int rdlen;
        if((rdlen = ns_rr_rdlen(*rr)) < 20) {
            return unexpected<Error>(Error{
                std::string("SOA record too short: " + std::to_string(rdlen)),
                0
            });
        }

        /*************************************************/
        /* Extract SOA record parts.                     */
        /*************************************************/
        int n;
        char mname[NS_MAXDNAME];
        char rname[NS_MAXDNAME];
        uint32_t serial;
        uint32_t refresh;
        uint32_t retry;
        uint32_t expire;
        uint32_t minimum;

        const unsigned char * cp = ns_rr_rdata(*rr);

        n = ns_name_uncompress(ns_msg_base(*handle), ns_msg_end(*handle), cp, mname, sizeof(mname));
        if(n < 0) {
            return unexpected<Error>(Error{
                std::string("Failed to extract MNAME from SOA record"),
                0
            });
        }
        cp += n;

        n = ns_name_uncompress(ns_msg_base(*handle), ns_msg_end(*handle), cp, rname, sizeof(rname));
        if(n < 0) {
            return unexpected<Error>(Error{
                std::string("Failed to extract RNAME from SOA record"),
                0
            });
        }
        cp += n;

        serial = ns_get32(cp);
        cp += sizeof(serial);

        refresh = ns_get32(cp);
        cp += sizeof(refresh);

        retry = ns_get32(cp);
        cp += sizeof(retry);

        expire = ns_get32(cp);
        cp += sizeof(expire);

        minimum = ns_get32(cp);

        /*************************************************/
        /* Append the SOA record to the  answers vector. */
        /*************************************************/
        return Answer({std::string(ns_rr_name(*rr)), "SOA",
                    /*std::string(mname)*/std::string("bizbaz")      + " " + std::string(rname)
            + " " + std::to_string(serial)  + " " + std::to_string(refresh)
            + " " + std::to_string(retry)   + " " + std::to_string(expire)
            + " " + std::to_string(minimum), minimum});
    }
}
