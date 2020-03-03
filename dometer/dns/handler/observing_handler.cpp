#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "dometer/dns/message/message.hpp"
#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/event/lookup_event.hpp"
#include "dometer/dns/event/query_event.hpp"
#include "dometer/dns/event/reply_event.hpp"
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
        innerHandler->on(dns::event::EventType::LOOKUP, [this](std::shared_ptr<dns::event::Event> event) {
            auto builder = dns::metrics::LookupObservation::newBuilder();
            auto lookupEvent = std::dynamic_pointer_cast<dns::event::LookupEvent>(event);
            auto query = lookupEvent->getQuery();

            builder.error("-");
            if(auto question = query.getQuestion()) {
                builder.qclass(question->qclass)
                       .qname(question->qname)
                       .qtype(question->qtype)
                       .duration(lookupEvent->getDuration().count());
                auto reply = lookupEvent->getReply();
                if(reply) {
                    builder.rcode(reply->getRCode());
                } else {
                    builder.error(dometer::dns::resolver::to_string(reply.error().code));
                    builder.rcode("-");
                }
            }

            this->observer->observe(dns::metrics::LookupSummary::INSTANCE, builder.build());
        });
    }

    std::x::expected<std::vector<uint8_t>, util::Error> ObservingHandler::handle(
        uint64_t sessionId, std::vector<uint8_t> queryBytes
    ) {
        return innerHandler->handle(sessionId, queryBytes);
    }

    Handler& ObservingHandler::on(dns::event::EventType eventType,
                                  util::Callback<std::shared_ptr<dns::event::Event>> listener) {
        innerHandler->on(eventType, listener);
        return *this;
    }
}
