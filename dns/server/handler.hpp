#pragma once

#include <memory>

#include "dns/server/event.hpp"
#include "dns/server/event_type.hpp"
#include "experimental/expected.hpp"
#include "util/callback.hpp"
#include "util/error.hpp"

namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Dns::Server {
    class Handler {
        public:
            virtual expected<size_t, Util::Error> handle(
                    uint8_t *queryPtr, size_t querySize,
                    uint8_t *replyPtr, size_t replySize) = 0;
            virtual Handler& on(EventType, Util::Callback<std::shared_ptr<Event>>) = 0;
    };
}