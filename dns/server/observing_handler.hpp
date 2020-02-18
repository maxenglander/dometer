#pragma once

#include <chrono>
#include <memory>

#include "dns/server/event_type.hpp"
#include "dns/server/handler.hpp"
#include "metrics/observer.hpp"
#include "util/error.hpp"
#include "x/expected.hpp"

namespace dometer::dns {
    class Packet;
}

namespace util = dometer::util;

namespace dometer::dns::server {
    class ObservingHandler : public Handler {
        public:
            ObservingHandler(
                    std::shared_ptr<Handler>,
                    std::shared_ptr<dometer::metrics::Observer>);
            std::x::expected<size_t, util::Error> handle(
                    uint8_t *queryPtr, size_t querySize,
                    uint8_t *replyPtr, size_t replySize);
            Handler& on(EventType, util::Callback<std::shared_ptr<Event>>);
        private:
            const std::shared_ptr<Handler> innerHandler;
            const std::shared_ptr<dometer::metrics::Observer> observer;
    };
}
