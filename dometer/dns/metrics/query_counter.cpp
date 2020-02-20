#include <string>
#include <tuple>

#include "dometer/dns/type.hpp"
#include "dometer/dns/metrics/labels.hpp"
#include "dometer/dns/metrics/query_counter.hpp"
#include "dometer/dns/metrics/type_label.hpp"
#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/labels.hpp"

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
