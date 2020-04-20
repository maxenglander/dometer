#pragma once

#include <memory>
#include <unordered_map>

#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/session/session.hpp"
#include "dometer/metrics/recorder.hpp"

namespace dometer::dns::eventmetrics {
    class metric_recording_callback {
        public:
            metric_recording_callback(std::shared_ptr<dometer::metrics::recorder>);
            metric_recording_callback(const metric_recording_callback&) = delete;
            metric_recording_callback(metric_recording_callback&&);
            void operator () (dometer::dns::event::any_event);
        private:
            const std::shared_ptr<dometer::metrics::recorder> recorder;
            std::unordered_map<uint64_t, dometer::dns::event::session> sessions;
    };
}
