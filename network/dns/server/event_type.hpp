#pragma once

namespace Dometer::Network::Dns::Server {
    enum class EventType {
        QUERY_RECEIVED,
        QUERY_REJECTED,
        QUERY_RESOLVED,
    };
}
