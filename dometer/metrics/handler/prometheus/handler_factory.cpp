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
#include "std/x/unique.hpp"
#include "std/x/variant.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    handler_factory::collectable_registrar::collectable_registrar(std::shared_ptr<::prometheus::Registry> registry)
        :   registry(registry)
    {}

    template <class ConcreteTransport>
    void handler_factory::collectable_registrar::operator()(ConcreteTransport& transport) {
        transport.RegisterCollectable(registry);
    }

    std::x::expected<std::unique_ptr<handler>, util::error> handler_factory::make_handler(options _options) {
        auto registry = std::make_shared<::prometheus::Registry>();
        std::vector<std::shared_ptr<::prometheus::x::Transport>> transports;
        collectable_registrar registrar(registry);

        for(auto it = _options.transports.begin(); it < _options.transports.end(); it++) {
            auto transport_result = transport_factory::make_transport(*it);
            if(transport_result) {
                auto transport = *transport_result;
                std::x::visit(registrar, *transport);
                transports.push_back(transport);
            } else {
                return std::x::unexpected<util::error>(util::error(
                    "Failed to create prometheus transport.",
                    transport_result.error()
                ));
            }
        }

        return std::x::make_unique<handler>(_options.max_time_series, registry, transports);
    }
}
