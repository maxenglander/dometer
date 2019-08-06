#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <cstdio>
#include <cstring>
#include <resolv.h>
#include <string>

#include "dns/answer.h"
#include "dns/resolver.h"
#include "dns/result.h"

#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::Dns {
    expected<Result, int> Resolver::lookupA(std::string name) {
        std::vector<Answer> answers;
        int len;

        unsigned char nsbuf[NS_PACKETSZ];

        /*************************************************/
        /* Perform a DNS lookup using any search domains */
        /* defined in /etc/resolv.conf. See resolv(2).   */
        /*************************************************/
        len = res_search(name.c_str(), C_IN, T_A, nsbuf, sizeof(nsbuf));
        if(len < 0) {
            return unexpected(0);
        }

        /*************************************************/
        /* Parse the DNS response.                       */
        /*************************************************/
        ns_msg handle;
        ns_initparse(nsbuf, len, &handle);

        /*************************************************/
        /* Iterate over each answer.                     */
        /*************************************************/
        for(int rrnum = 0; rrnum < ns_msg_count(handle, ns_s_an); rrnum++) {
            ns_rr rr;

            /*************************************************/
            /* Parse the answer section into a record.       */
            /*************************************************/
            if(ns_parserr(&handle, ns_s_an, rrnum, &rr) < 0) {
                return unexpected(0);
            }

            if(ns_rr_type(rr) != ns_t_a) {
                continue;
            }

            /*************************************************/
            /* Extract the IP address and TTL.               */
            /*************************************************/
            char ip[INET_ADDRSTRLEN];
            u_int32_t ttl;
            inet_ntop(AF_INET, ns_rr_rdata(rr), ip, INET_ADDRSTRLEN);
            ttl = ns_rr_ttl(rr);

            /*************************************************/
            /* Append the IP and TTL to the answers vector.  */
            /*************************************************/
            answers.push_back(Answer("A", name, ip, ttl));
        }

        return Result::success(answers);
    }
}
