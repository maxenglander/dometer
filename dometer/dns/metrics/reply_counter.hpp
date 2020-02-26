#pragma once

#include "dometer/metrics/counter.hpp"

namespace dometer::dns::metrics {
    struct ReplyCounter : dometer::metrics::Counter<
                              /*qclass*/std::string,
                              /*qname*/ std::string,
                              /*qtype*/ std::string,
                              /*rcode*/ std::string,
                              /*valid*/ bool
                          > {
        static const ReplyCounter INSTANCE;

        private:
            ReplyCounter();
    };
}
