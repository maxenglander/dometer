#pragma once

#include <memory>

#include "dometer/dns/event/event.hpp"
#include "dometer/dns/event/event_type.hpp"
#include "std/x/expected.hpp"
#include "dometer/util/callback.hpp"
#include "dometer/util/error.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::handler {
    class Handler {
        public:
            virtual std::x::expected<size_t, util::Error> handle(
                    uint8_t *queryPtr, size_t querySize,
                    uint8_t *replyPtr, size_t replySize) = 0;
            virtual Handler& on(dns::event::EventType,
                                util::Callback<std::shared_ptr<dns::event::Event>>) = 0;
    };
}
