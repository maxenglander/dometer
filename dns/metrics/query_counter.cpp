#include <string>
#include <tuple>

#include "dns/type.hpp"
#include "dns/metrics/labels.hpp"
#include "dns/metrics/query_counter.hpp"
#include "dns/metrics/type_label.hpp"
#include "metrics/counter.hpp"
#include "metrics/labels.hpp"

namespace Dometer::Dns::Metrics {
    const QueryCounter QueryCounter::INSTANCE = QueryCounter();

    QueryCounter::QueryCounter()
            :   Dometer::Metrics::Counter<std::string, std::string, Dometer::Dns::Type, bool>::Counter(
                    "dns_query_count", "Count of DNS queries received",
                    std::make_tuple(
                        Dometer::Metrics::Labels::string("qclass"), 
                        Dometer::Metrics::Labels::string("qname"),
                        Labels::type("qtype"),
                        Dometer::Metrics::Labels::boolean("valid")
                    )
                )
    {}
}
