#pragma once

#include <string>

#include "metrics/prometheus_types.hpp"
#include "util/lru_map.hpp"

namespace Util = Dometer::Util;

namespace Dometer::Metrics {
    class PrometheusLRUMap : public Util::LRUMap<prometheus::ext::AnyMetricPtr, std::string> {
        public:
            PrometheusLRUMap(size_t maxTimeSeries);
        protected:
            void erase(prometheus::ext::AnyMetricPtr);
            void insert(prometheus::ext::AnyMetricPtr, std::string);
            bool shouldEvict();
        private:
            size_t numTimeSeries;
            const size_t maxTimeSeries;
    };
}
