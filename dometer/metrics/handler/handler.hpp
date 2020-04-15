#pragma once

#include <map>
#include <string>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/histogram.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::metrics::handler {
    class handler {
        public:
            virtual void increment(const dometer::metrics::counter&, std::map<std::string, std::string>, uint64_t) = 0;
            virtual void record(const dometer::metrics::histogram&, std::map<std::string, std::string>, double) = 0;
            virtual void record(const dometer::metrics::summary&, std::map<std::string, std::string>, double) = 0;
    };
}
