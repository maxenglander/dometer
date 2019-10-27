#pragma once

namespace Dometer::Dns {
    enum class Opcode {
        QUERY = 0,
        IQUERY = 1,
        STATUS = 2,
        NOTIFY = 4,
        UPDATE = 5,
        DSO = 6
    };
}
