#pragma once

namespace dometer::dns::message {
    enum class opcode {
        query = 0,
        iquery = 1,
        status = 2,
        notify = 4,
        update = 5,
        dso = 6
    };
}
