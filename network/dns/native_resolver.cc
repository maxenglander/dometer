#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <cstdio>
#include <cstring>
#include <netdb.h>
#include <resolv.h>
#include <string>

#include "network/dns/answer.h"
#include "network/dns/header.h"
#include "network/dns/native_resolver.h"
#include "std/experimental/expected.h"
#include "util/error.h"

using namespace std::experimental;

namespace DnsTelemeter::Network::Dns {
    expected<Response, Error> NativeResolver::lookupA(std::string name) {
        int len;
        unsigned char nsbuf[NS_PACKETSZ];

        /*************************************************/
        /* Perform a DNS lookup using any search domains */
        /* defined in /etc/resolv.conf. See resolv(2).   */
        /*************************************************/
        len = res_search(name.c_str(), C_IN, T_A, nsbuf, sizeof(nsbuf));
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
            answers.push_back(Answer{"A", name, ip, ttl});
        }

        return Response{
            Header{rcode},
            answers
        };
    }
}
