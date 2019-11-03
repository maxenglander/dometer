#include <string>
#include <tuple>

#include "dns/type.hpp"
#include "dns/metrics/labels.hpp"
#include "dns/metrics/query_counter.hpp"
#include "dns/metrics/type_label.hpp"
#include "metrics/counter.hpp"
#include "metrics/labels.hpp"

namespace dometer::dns::metrics {
    const QueryCounter QueryCounter::INSTANCE = QueryCounter();

    QueryCounter::QueryCounter()
            :   dometer::metrics::Counter<std::string, std::string, dometer::dns::Type, bool>::Counter(
                    "dns_query_received_count", "Count of DNS queries received by Dometer",
                    std::make_tuple(
                        dometer::metrics::Labels::string("qclass"), 
                        dometer::metrics::Labels::string("qname"),
                        Labels::type("qtype"),
                        dometer::metrics::Labels::boolean("valid")
                    )
                )
    {}
}
