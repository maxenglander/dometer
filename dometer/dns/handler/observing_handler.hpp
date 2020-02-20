#pragma once

#include <chrono>
#include <memory>

#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/metrics/observer.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns {
    class Packet;
}

namespace dns = dometer::dns;
namespace metrics = dometer::metrics;
namespace util = dometer::util;

namespace dometer::dns::handler {
    class ObservingHandler : public Handler {
        public:
            ObservingHandler(
                    std::shared_ptr<Handler>,
                    std::shared_ptr<metrics::Observer>);
            std::x::expected<size_t, util::Error> handle(
                    uint8_t *queryPtr, size_t querySize,
                    uint8_t *replyPtr, size_t replySize);
            Handler& on(dns::event::EventType, util::Callback<std::shared_ptr<dns::event::Event>>);
        private:
            const std::shared_ptr<Handler> innerHandler;
            const std::shared_ptr<metrics::Observer> observer;
    };
}
