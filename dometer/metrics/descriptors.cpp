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
    const Descriptor<std::string, std::string, std::string, bool> Descriptors::QUERY(
        "dns_query_count", "Count of DNS queries received",
        std::make_tuple(
            Labels::string("qclass"), 
            Labels::string("qname"),
            Labels::string("qtype"),
            Labels::boolean("valid")
        ),
        type::COUNTER, Unit::NONE
    );
}
