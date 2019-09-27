#pragma once

namespace Dometer::Network::Dns {
    enum class Rcode {
        NOERROR = 0,
        FORMERR = 1,
        SERVFAIL = 2,
        NXDOMAIN = 3,
        NOTIMP = 4,
        REFUSED = 5
    };
}
