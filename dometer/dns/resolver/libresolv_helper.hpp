#pragma once

#include <resolv.h>
#include <string>

namespace dometer::dns::resolver {
    class libresolv_helper {
        public:
            static struct __res_state make_res_state_for_nameserver(std::string host, uint16_t port);
    };
}
