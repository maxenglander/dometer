#include <iostream>
#include <memory>
#include <vector>

#include "dometer/metrics/handler/prometheus/handler.hpp"
#include "dometer/metrics/handler/prometheus/handler_factory.hpp"
#include "dometer/metrics/handler/prometheus/options.hpp"
#include "dometer/metrics/handler/prometheus/transport_factory.hpp"
#include "dometer/util/error.hpp"
#include "prometheus/registry.h"
#include "std/x/expected.hpp"
#include "std/x/variant.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    handler_factory::CollectableRegistrar::CollectableRegistrar(std::shared_ptr<::prometheus::Registry> registry)
        :   registry(registry)
    {}

    template <class ConcreteTransport>
    void handler_factory::CollectableRegistrar::operator()(ConcreteTransport& transport) {
        transport.RegisterCollectable(registry);
    }

    std::x::expected<Handler, util::error> handler_factory::makeHandler(options options) {
        auto registry = std::make_shared<::prometheus::Registry>();
        std::vector<std::shared_ptr<::prometheus::x::Transport>> transports;
        CollectableRegistrar registrar(registry);

        for(auto it = options.transports.begin(); it < options.transports.end(); it++) {
            auto transportResult = TransportFactory::makeTransport(*it);
            if(transportResult) {
                auto transport = *transportResult;
                std::x::visit(registrar, *transport);
                transports.push_back(transport);
            } else {
                return std::x::unexpected<util::error>(util::error(
                    "Failed to create prometheus transport.",
                    transportResult.error()
                ));
            }
        }

        Handler handler(options.maxTimeSeries, registry, transports);
        return handler;
    }
}
