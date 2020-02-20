#pragma once

#include "dometer/metrics/counter.hpp"

namespace dometer::dns::metrics {
    struct ReplyCounter : dometer::metrics::Counter<std::string, std::string, std::string, bool> {
        static const ReplyCounter INSTANCE;

        private:
            ReplyCounter();
    };
}
