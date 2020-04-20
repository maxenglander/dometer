#include <vector>

#include "gmock/gmock.h"
#include "prometheus/metric_family.h"
#include "prometheus/registry.h"

namespace prometheus::x {
    class MockRegistry : public prometheus::Registry {
        public:
            MOCK_METHOD((std::vector<MetricFamily>), Collect, void, (const, override));
    };
}
