#include <string>
#include <tuple>
#include <utility>

#include "metrics/counter_descriptor.hpp"
#include "metrics/descriptor.hpp"
#include "metrics/descriptors.hpp"
#include "metrics/labels.hpp"
#include "metrics/type.hpp"
#include "metrics/unit.hpp"

namespace Dometer::Metrics {
    const Descriptor<std::string, std::string, std::string, bool> Descriptors::QUERY(
        "dns_query_count", "Count of DNS queries received",
        std::make_tuple(
            Labels::string("qclass"), 
            Labels::string("qname"),
            Labels::string("qtype"),
            Labels::boolean("valid")
        ),
        Type::COUNTER, Unit::NONE
    );
}
