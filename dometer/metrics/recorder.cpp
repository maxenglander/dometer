#include <map>
#include <memory>
#include <string>
#include <vector>

#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/histogram.hpp"
#include "dometer/metrics/recorder.hpp"

namespace dometer::metrics {
    recorder::recorder()
        : _additional_labels(), _handlers()
    {}

    recorder::recorder(std::map<std::string, std::string> additional_labels,
                       std::vector<std::unique_ptr<dometer::metrics::handler::handler>> handlers)
        : _additional_labels(additional_labels), _handlers(std::move(handlers))
    {}

    void recorder::record(const histogram& histogram, std::map<std::string, std::string> labels, double value) {
        std::map<std::string, std::string> merged_labels;
        merged_labels.insert(_additional_labels.begin(), _additional_labels.end());
        merged_labels.insert(labels.begin(), labels.end());

        for(auto it = _handlers.begin(); it < _handlers.end(); it++) {
            (*it)->record(histogram, merged_labels, value);
        }
    }
}
