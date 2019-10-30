#pragma once

#include "metrics/counter.hpp"

namespace Dometer::Dns::Metrics {
    struct ReplyCounter : Dometer::Metrics::Counter<std::string, std::string, std::string, bool> {
        static const ReplyCounter INSTANCE;

        private:
            ReplyCounter();
    };
}
