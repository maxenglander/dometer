#pragma once

#include <memory>

#include "dometer/metrics/handler/prometheus_handler.hpp"
#include "dometer/metrics/handler/prometheus_options.hpp"
#include "dometer/util/error.hpp"
#include "prometheus/registry.h"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler {
    class PrometheusHandlerFactory {
        class CollectableRegistrar {
            public:
                CollectableRegistrar(std::shared_ptr<prometheus::Registry>);
                template <class ConcreteTransport>
                void operator()(ConcreteTransport&);
            private:
                std::shared_ptr<prometheus::Registry> registry;
        };

        public:
            static std::x::expected<PrometheusHandler, util::Error> makeHandler(PrometheusOptions options);
    };
}
