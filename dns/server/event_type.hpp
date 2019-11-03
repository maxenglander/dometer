#pragma once

#include <stddef.h>

namespace dometer::dns::server {
    enum class EventType {
        LOOKUP,
        QUERY,
        REPLY
    };
}

namespace std {
    template <> struct hash<dometer::dns::server::EventType> {
        size_t operator()(const dometer::dns::server::EventType& t) const noexcept {
            return size_t(t);
        }
    };
}
