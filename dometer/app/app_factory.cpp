#include <memory>
#include <utility>

#include "dometer/app/app.hpp"
#include "dometer/app/app_factory.hpp"
#include "dometer/app/options.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/options.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/handler/resolving_handler.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/dns/resolver/resolver_factory.hpp"
#include "dometer/dns/server/basic_server.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/event/emitter.hpp"
#include "dometer/metrics/handler/handler_factory.hpp"
#include "dometer/metrics/options.hpp"
#include "dometer/metrics/recorder.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"
#include "std/x/unique.hpp"

namespace dometer::app {
    std::x::expected<std::shared_ptr<dometer::app::app>, dometer::util::error> app_factory::make_app(dometer::app::options options) {
        auto recorder = make_recorder(options.metrics);
        if(!recorder)
            return std::x::unexpected<dometer::util::error>(recorder.error());

        auto emitter = std::make_shared<event::emitter<dometer::dns::event::any_event>>();

        auto resolver = make_resolver(options.dns.resolver);
        if(!resolver)
            return std::x::unexpected<dometer::util::error>(resolver.error());

        auto server = make_server(emitter, *resolver);
        return std::make_shared<dometer::app::app>(emitter, *recorder, server);
    }

    std::x::expected<std::shared_ptr<dometer::metrics::recorder>, dometer::util::error> app_factory::make_recorder(
            const dometer::metrics::options options) {
        auto handlers_result = dometer::metrics::handler::handler_factory::make_handlers(options.handlers);
        if(!handlers_result) {
            return std::x::unexpected<dometer::util::error>(dometer::util::error(
                "Failed to create metrics handlers.",
                handlers_result.error()
            ));
        } else {
            return std::make_shared<dometer::metrics::recorder>(options.additional_labels, std::move(*handlers_result));
        }
    }

    std::x::expected<std::shared_ptr<dometer::dns::resolver::resolver>, dometer::util::error> app_factory::make_resolver(
            dometer::dns::resolver::options options) {
        auto resolver = dometer::dns::resolver::resolver_factory::make_resolver(options);
        if(!resolver) {
            return std::x::unexpected<dometer::util::error>(dometer::util::error(
                "Failed to create resolver.",
                resolver.error()
            ));
        } else {
            return resolver;
        }
    }

    std::shared_ptr<dometer::dns::server::server> app_factory::make_server(
            std::shared_ptr<dometer::event::emitter<dometer::dns::event::any_event>> emitter,
            std::shared_ptr<dometer::dns::resolver::resolver> resolver) {
        auto resolving_handler = std::make_shared<dometer::dns::handler::resolving_handler>(emitter, resolver);
        return std::make_shared<dometer::dns::server::basic_server>(emitter, resolving_handler);
    }
}
