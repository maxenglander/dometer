#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "dometer/dns/message/message.hpp"
#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/handler/observing_handler.hpp"
#include "dometer/dns/metrics/lookup_observation.hpp"
#include "dometer/dns/metrics/lookup_summary.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::handler {
    ObservingHandler::ObservingHandler(std::shared_ptr<dns::handler::Handler> handler,
                                       std::shared_ptr<dometer::metrics::Observer> observer)
        :   innerHandler(handler), observer(observer)
    {
    }

    std::x::expected<std::vector<uint8_t>, util::Error> ObservingHandler::handle(
        uint64_t sessionId, std::vector<uint8_t> queryBytes
    ) {
        return innerHandler->handle(sessionId, queryBytes);
    }
}
