#pragma once

#include <memory>

#include "dns/server/event.hpp"
#include "dns/server/event_type.hpp"
#include "x/expected.hpp"
#include "util/callback.hpp"
#include "util/error.hpp"

namespace util = dometer::util;
using namespace std::x;

namespace dometer::dns::server {
    class Handler {
        public:
            virtual expected<size_t, util::Error> handle(
                    uint8_t *queryPtr, size_t querySize,
                    uint8_t *replyPtr, size_t replySize) = 0;
            virtual Handler& on(EventType, util::Callback<std::shared_ptr<Event>>) = 0;
    };
}
