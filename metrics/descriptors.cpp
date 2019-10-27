#include <string>
#include <tuple>

#include "metrics/descriptor.hpp"
#include "metrics/descriptors.hpp"
#include "metrics/labels.hpp"
#include "metrics/unit.hpp"

namespace Dometer::Metrics {
    const Descriptor<std::string, bool> Descriptors::QUERY
        = Descriptor<std::string, bool>("query", "DNS query received", Unit::NONE,
                                        tuple(Labels::string("qname"), 
                                              Labels::boolean("valid")));
}
