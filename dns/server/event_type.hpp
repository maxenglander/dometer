#pragma once

#include <stddef.h>

namespace Dometer::Dns::Server {
    enum class EventType {
        LOOKUP,
        QUERY,
        REPLY
    };
}

namespace std {
    template <> struct hash<Dometer::Dns::Server::EventType> {
        size_t operator()(const Dometer::Dns::Server::EventType& t) const noexcept {
            return size_t(t);
        }
    };
}
