#include <map>
#include <memory>
#include <vector>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/recorder.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::metrics {
    recorder::recorder()
        : handlers()
    {}

    recorder::recorder(std::vector<std::unique_ptr<dometer::metrics::handler::handler>> handlers)
        : handlers(std::move(handlers))
    {}

    void recorder::increment(const counter& counter, std::map<std::string, std::string> labels, uint64_t value) {
        for(auto it = handlers.begin(); it < handlers.end(); it++) {
            (*it)->increment(counter, labels, value);
        }
    }

    void recorder::record(const summary& summary, std::map<std::string, std::string> labels, double value) {
        for(auto it = handlers.begin(); it < handlers.end(); it++) {
            (*it)->record(summary, labels, value);
        }
    }
}
