#include <string>
#include <tuple>

#include "metrics/descriptor.hpp"
#include "metrics/descriptors.hpp"
#include "metrics/labels.hpp"
#include "metrics/unit.hpp"

namespace Dometer::Metrics {
    const Descriptor<std::string, bool> Descriptors::QUERY{"query", "DNS query received",
                                        std::make_tuple(
                                            Labels::string("qname"), 
                                            Labels::boolean("valid")
                                        ),
                                        Unit::NONE};
}
