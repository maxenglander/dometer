#pragma once

#include <memory>
#include <unordered_map>

#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/event/session.hpp"
#include "dometer/metrics/observer.hpp"

namespace dometer::dns::eventmetrics {
    class metric_recording_event_functor {
        public:
            metric_recording_event_functor(std::shared_ptr<dometer::metrics::observer>);
            metric_recording_event_functor(const metric_recording_event_functor&);
            ~metric_recording_event_functor();
            void operator () (dometer::dns::event::any_event);
        private:
            const std::shared_ptr<dometer::metrics::observer> observer;
            std::unordered_map<uint64_t, dometer::dns::event::Session> sessions;
    };
}