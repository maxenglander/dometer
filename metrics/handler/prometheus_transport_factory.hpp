#pragma once

#include  <memory>

#include "metrics/handler/prometheus_transport_options.hpp"
#include "metrics/handler/prometheus_types.hpp"

namespace dometer::metrics::handler {
    class PrometheusTransportFactory {
        public:
            static std::shared_ptr<prometheus::x::Transport> makeTransport(PrometheusTransportOptions);
    };
}
