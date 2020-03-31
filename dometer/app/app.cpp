#include <memory>
#include <string>

#include "dometer/app/app.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/eventmetrics/metric_recording_callback.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/event/emitter.hpp"
#include "dometer/metrics/recorder.hpp"
#include "dometer/util/error.hpp"

namespace dometer::app {
    app::app(std::shared_ptr<dometer::event::emitter<dometer::dns::event::any_event>> emitter,
             std::shared_ptr<dometer::metrics::recorder> recorder,
             std::shared_ptr<dometer::dns::server::server> server)
        :  _callback(std::make_shared<dometer::dns::eventmetrics::metric_recording_callback>(recorder)),
           _emitter(emitter), _recorder(recorder), _server(server)
    {
        _emitter->on([&](dometer::dns::event::any_event event) {
            (*_callback)(event);
        });
    }

    void app::join() {
        _server->join();
    }

    std::x::expected<void, dometer::util::error> app::start(std::string bindAddress) {
        return _server->start(bindAddress);
    }

    void app::stop() {
        _server->stop();
    }
}
