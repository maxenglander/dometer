#pragma once

#include  <memory>

#include "dometer/metrics/handler/prometheus/transport_options.hpp"
#include "dometer/util/error.hpp"
#include "prometheus/x/types.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    class TransportFactory {
        public:
            static std::x::expected<std::shared_ptr<::prometheus::x::Transport>, util::error> makeTransport(TransportOptions);
    };
}
