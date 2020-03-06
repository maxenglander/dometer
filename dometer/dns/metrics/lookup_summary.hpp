#pragma once

#include <string>

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::dns::metrics {
    struct LookupSummary : dometer::metrics::Summary<
                               /* error  */std::string,
                               /* qclass */dometer::dns::dns_class,
                               /* qname  */std::string,
                               /* qtype  */dometer::dns::type,
                               /* rcode  */std::string
                           > {
        static const LookupSummary INSTANCE;

        private:
            LookupSummary();
    };
}
