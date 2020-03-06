#pragma once

namespace dometer::metrics {
    enum class type {
        COUNTER,
        GUAGE,
        HISTOGRAM,
        SUMMARY
    };
}
