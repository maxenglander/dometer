#pragma once

#include <stddef.h>

namespace Dometer::Network::Dns::Server {
    enum class EventType {
        LOOKUP,
        QUERY,
        REPLY
    };
}

namespace std {
    template <> struct hash<Dometer::Network::Dns::Server::EventType> {
        size_t operator()(const Dometer::Network::Dns::Server::EventType& t) const noexcept {
            return size_t(t);
        }
    };
}
