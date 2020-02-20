#pragma once

namespace dometer::metrics {
    enum class Type {
        COUNTER,
        GUAGE,
        HISTOGRAM,
        SUMMARY
    };
}
