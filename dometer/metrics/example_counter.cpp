#include <string>
#include <vector>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/example_counter.hpp"

namespace dometer::metrics {
    const example_counter example_counter::instance = example_counter();

    example_counter::example_counter() : dometer::metrics::counter(
        "example_count",
        "Example of a counter."
    ) {}
}
