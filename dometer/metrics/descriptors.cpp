#include <string>
#include <tuple>
#include <utility>

#include "dometer/metrics/counter_descriptor.hpp"
#include "dometer/metrics/descriptor.hpp"
#include "dometer/metrics/descriptors.hpp"
#include "dometer/metrics/labels.hpp"
#include "dometer/metrics/type.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    const descriptor<std::string, std::string, std::string, bool> descriptors::query(
        "dns_query_count", "Count of DNS queries received",
        std::make_tuple(
            labels::string("qclass"), 
            labels::string("qname"),
            labels::string("qtype"),
            labels::boolean("valid")
        ),
        type::counter, unit::none
    );
}
