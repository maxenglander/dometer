#pragma once

#include <map>
#include <memory>
#include <vector>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::metrics {
    class recorder {
        public:
            recorder() = delete;
            recorder(const recorder&) = delete;
            recorder(recorder&&) = delete;
            recorder(std::vector<std::unique_ptr<dometer::metrics::handler::handler>>);
            void increment(const counter&, std::map<std::string, std::string>, uint64_t);
            void record(const summary&, std::map<std::string, std::string>, double);
        private:
            std::vector<std::unique_ptr<dometer::metrics::handler::handler>> handlers;
    };
}
