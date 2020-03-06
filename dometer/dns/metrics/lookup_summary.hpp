#pragma once

#include <string>

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::dns::metrics {
    struct lookup_summary : dometer::metrics::summary<
                               /* error  */std::string,
                               /* qclass */dometer::dns::class_,
                               /* qname  */std::string,
                               /* qtype  */dometer::dns::type,
                               /* rcode  */std::string
                           > {
        static const lookup_summary instance;

        private:
            lookup_summary();
    };
}
