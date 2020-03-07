#pragma once

namespace dometer::metrics {
    enum class type {
        counter,
        gauge,
        histogram,
        summary
    };
}
