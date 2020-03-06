#pragma once

#include <memory>

#include "dometer/metrics/handler/prometheus/handler.hpp"
#include "dometer/metrics/handler/prometheus/options.hpp"
#include "dometer/util/error.hpp"
#include "prometheus/registry.h"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    class handler_factory {
        class CollectableRegistrar {
            public:
                CollectableRegistrar(std::shared_ptr<::prometheus::Registry>);
                template <class ConcreteTransport>
                void operator()(ConcreteTransport&);
            private:
                std::shared_ptr<::prometheus::Registry> registry;
        };

        public:
            static std::x::expected<Handler, util::error> makeHandler(options options);
    };
}
