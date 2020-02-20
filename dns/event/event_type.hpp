#pragma once

#include <stddef.h>

namespace dometer::dns::event {
    enum class EventType {
        LOOKUP,
        QUERY,
        REPLY
    };
}

namespace std {
    template <> struct hash<dometer::dns::event::EventType> {
        size_t operator()(const dometer::dns::event::EventType& t) const noexcept {
            return size_t(t);
        }
    };
}
