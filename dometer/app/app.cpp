#include <memory>

#include "dometer/app/app.hpp"
#include "dometer/app/options.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/util/error.hpp"

namespace dometer::app {
    app::app(dometer::app::options options, std::shared_ptr<dometer::dns::server::server> server)
        :   _options(options),
            _server(server)
    {}

    void app::join() {
        _server->join();
    }

    std::x::expected<void, dometer::util::error> app::start() {
        return _server->start(_options.dns.server.transport.bind_address);
    }

    void app::stop() {
        _server->stop();
    }
}
