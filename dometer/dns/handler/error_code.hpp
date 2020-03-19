#pragma once

namespace dometer::dns::handler {
    enum class error_code {
        invalid_query,
        invalid_reply,
        resolver_failure,
    };
}
