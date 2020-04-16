#pragma once

#include <memory>

#include "dometer/app/app.hpp"
#include "dometer/app/options.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/options.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/event/emitter.hpp"
#include "dometer/metrics/recorder.hpp"
#include "dometer/metrics/options.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::app {
    class app_factory {
        public:
            static std::x::expected<std::shared_ptr<dometer::app::app>, dometer::util::error> make_app(options);
        private:
            static std::x::expected<std::shared_ptr<dometer::metrics::recorder>, dometer::util::error> make_recorder(
                    const dometer::metrics::options);
            static std::x::expected<std::shared_ptr<dometer::dns::resolver::resolver>, dometer::util::error> make_resolver(
                    dometer::dns::resolver::options);
            static std::shared_ptr<dometer::dns::server::server> make_server(
                    std::shared_ptr<dometer::event::emitter<dometer::dns::event::any_event>>,
                    std::shared_ptr<dometer::dns::resolver::resolver>);
    };
}
