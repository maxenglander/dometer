#pragma once

namespace Dometer::Dns {
    enum class RCode {
        NOERROR = 0,
        FORMERR = 1,
        SERVFAIL = 2,
        NXDOMAIN = 3,
        NOTIMP = 4,
        REFUSED = 5
    };
}
