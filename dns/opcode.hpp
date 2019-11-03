#pragma once

namespace dometer::dns {
    enum class OpCode {
        QUERY = 0,
        IQUERY = 1,
        STATUS = 2,
        NOTIFY = 4,
        UPDATE = 5,
        DSO = 6
    };
}
