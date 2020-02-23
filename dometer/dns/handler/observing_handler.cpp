#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "dometer/dns/packet.hpp"
#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/event/lookup_event.hpp"
#include "dometer/dns/event/query_event.hpp"
#include "dometer/dns/event/reply_event.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/handler/observing_handler.hpp"
#include "dometer/dns/metrics/lookup_observation.hpp"
#include "dometer/dns/metrics/lookup_summary.hpp"
#include "dometer/dns/metrics/query_counter.hpp"
#include "dometer/dns/metrics/query_observation.hpp"
#include "dometer/dns/metrics/reply_counter.hpp"
#include "dometer/dns/metrics/reply_observation.hpp"
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

            if(auto query = lookupEvent->getQuery()) {
                if(auto question = query.getQuestion()) {
                    builder.qclass(question->qclass)
                           .qname(question->qname)
                           .qtype(question->qtype)
                           .duration(lookupEvent->getDuration().count());
                }
            }

            this->observer->observe(dns::metrics::LookupSummary::INSTANCE, builder.build());
        });

        innerHandler->on(dns::event::EventType::QUERY, [this](std::shared_ptr<dns::event::Event> event) {
            auto builder = dns::metrics::QueryObservation::newBuilder();
            auto queryEvent = std::dynamic_pointer_cast<dns::event::QueryEvent>(event);

            builder.valid(false);
            if(auto query = queryEvent->getQuery()) {
                if(auto question = query->getQuestion()) {
                    builder.qclass(question->qclass)
                           .qname(question->qname)
                           .qtype(question->qtype)
                           .valid(true);
                }
            }

            this->observer->increment(dns::metrics::QueryCounter::INSTANCE, builder.build());
        });

        innerHandler->on(dns::event::EventType::REPLY, [this](std::shared_ptr<dns::event::Event> event) {
            auto builder = dns::metrics::ReplyObservation::newBuilder();
            auto queryEvent = std::dynamic_pointer_cast<dns::event::ReplyEvent>(event);

            builder.valid(false);
            if(auto reply = queryEvent->getReply()) {
                if(auto question = reply->getQuestion()) {
                    builder.qclass(question->qclass)
                           .qname(question->qname)
                           .qtype(question->qtype)
                           .valid(true);
                }
            }

            this->observer->increment(dns::metrics::ReplyCounter::INSTANCE, builder.build());
        });
    }

    std::x::expected<size_t, util::Error> ObservingHandler::handle(
            uint8_t *queryPtr, size_t querySize,
            uint8_t *replyPtr, size_t replySize) {
        return innerHandler->handle(queryPtr, querySize, replyPtr, replySize);
    }

    Handler& ObservingHandler::on(dns::event::EventType eventType,
                                  util::Callback<std::shared_ptr<dns::event::Event>> listener) {
        innerHandler->on(eventType, listener);
        return *this;
    }
}
