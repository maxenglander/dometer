#pragma once

#include <memory>
#include <unordered_map>

#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/event/session.hpp"
#include "dometer/metrics/observer.hpp"

namespace dometer::dns::eventmetrics {
    class MetricRecordingEventFunctor {
        public:
            MetricRecordingEventFunctor(std::shared_ptr<dometer::metrics::Observer>);
            MetricRecordingEventFunctor(const MetricRecordingEventFunctor&);
            ~MetricRecordingEventFunctor();
            void operator () (dometer::dns::event::AnyEvent);
        private:
            const std::shared_ptr<dometer::metrics::Observer> observer;
            std::unordered_map<uint64_t, dometer::dns::event::Session> sessions;
    };
}
