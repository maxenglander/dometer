#pragma once

#include <functional>
#include <stddef.h>

namespace dometer::dns::event {
    enum class EventType {
        PARSE_MESSAGE,
        RESOLVE_QUERY,
        START_SESSION
    };
}

namespace std {
    template <> struct hash<dometer::dns::event::EventType> {
        size_t operator()(const dometer::dns::event::EventType& t) const noexcept {
            return size_t(t);
        }
    };
}
