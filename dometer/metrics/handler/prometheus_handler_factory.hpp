#pragma once

#include <memory>

#include "dometer/metrics/handler/prometheus_handler.hpp"
#include "dometer/metrics/handler/prometheus_options.hpp"
#include "prometheus/registry.h"

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
            static PrometheusHandler makeHandler(PrometheusOptions options);
    };
}
