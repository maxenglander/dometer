#pragma once

#include <memory>
#include <string>

#include "dometer/event/emitter.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/eventmetrics/metric_recording_callback.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/metrics/recorder.hpp"
#include "dometer/util/error.hpp"

namespace dometer::app {
    class app {
        public:
            app(std::shared_ptr<dometer::event::emitter<dometer::dns::event::any_event>> emitter,
                std::shared_ptr<dometer::metrics::recorder> recorder,
                std::shared_ptr<dometer::dns::server::server>);
            void join();
            std::x::expected<void, dometer::util::error> start(std::string);
            void stop();
        private:
            std::shared_ptr<dometer::dns::eventmetrics::metric_recording_callback> _callback;
            std::shared_ptr<dometer::event::emitter<dometer::dns::event::any_event>> _emitter;
            std::shared_ptr<dometer::metrics::recorder> _recorder;
            std::shared_ptr<dometer::dns::server::server> _server;
    };
}
