#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/histogram.hpp"

namespace dometer::metrics {
    class recorder {
        public:
            recorder();
            recorder(const recorder&) = delete;
            recorder(recorder&&) = delete;
            recorder(std::map<std::string, std::string> additional_labels,
                     std::vector<std::unique_ptr<dometer::metrics::handler::handler>>);
            virtual void record(const histogram&, std::map<std::string, std::string>, double);
        private:
            std::map<std::string, std::string> _additional_labels;
            std::vector<std::unique_ptr<dometer::metrics::handler::handler>> _handlers;
    };
}
