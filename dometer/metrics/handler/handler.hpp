#pragma once

#include <map>
#include <string>

#include "dometer/metrics/histogram.hpp"

namespace dometer::metrics::handler {
    class handler {
        public:
            virtual void record(const dometer::metrics::histogram&, std::map<std::string, std::string>, double) = 0;
    };
}
