#include <string>
#include <vector>

#include "dometer/metrics/histogram.hpp"
#include "dometer/metrics/example_histogram.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    const example_histogram example_histogram::instance = example_histogram();

    example_histogram::example_histogram() : dometer::metrics::histogram(
        "example_count",
        "Example of a histogram.",
        std::vector<double>{{ 0.1, 10.0 }},
        unit::none
    ) {}
}
