#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <resolv.h>
#include <string>

#include "dometer/dns/resolver/libresolv_helper.hpp"

namespace dometer::dns::resolver {
    struct __res_state libresolv_helper::make_res_state_for_nameserver(std::string host, uint16_t port) {
        struct __res_state stat;

        res_ninit(&stat);

        struct in_addr addr;
        inet_pton(AF_INET, host.c_str(), &addr);

        // Normalize options as much as possible.
        stat.options = 0;
        stat.ndots = 1;
        stat.nscount = 1;
        stat.nsaddr_list[0] = (struct sockaddr_in) {
            .sin_family = AF_INET,
            .sin_port = htons(port),
            .sin_addr = addr,
        };
        stat.retry = 1;

        return stat;
    }
}
