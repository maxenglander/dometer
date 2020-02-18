#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "dns/packet.hpp"
#include "dns/metrics/lookup_observation.hpp"
#include "dns/metrics/lookup_summary.hpp"
#include "dns/metrics/query_counter.hpp"
#include "dns/metrics/query_observation.hpp"
#include "dns/metrics/reply_counter.hpp"
#include "dns/metrics/reply_observation.hpp"
#include "dns/server/event_type.hpp"
#include "dns/server/handler.hpp"
#include "dns/server/lookup_event.hpp"
#include "dns/server/observing_handler.hpp"
#include "dns/server/query_event.hpp"
#include "dns/server/reply_event.hpp"
#include "util/error.hpp"
#include "x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::server {
    ObservingHandler::ObservingHandler(std::shared_ptr<dns::server::Handler> handler,
                                       std::shared_ptr<dometer::metrics::Observer> observer)
        :   innerHandler(handler), observer(observer)
    {
        innerHandler->on(dns::server::EventType::LOOKUP, [this](auto event) {
            auto builder = dns::metrics::LookupObservation::newBuilder();
            auto lookupEvent = std::dynamic_pointer_cast<dns::server::LookupEvent>(event);

            if(auto query = lookupEvent->getQuery()) {
                if(auto question = query.getQuestion()) {
                    builder.qclass(question->qclass)
                           .qname(question->qname)
                           .qtype(question->qtype)
                           .duration(lookupEvent->getDuration().count());
                }
            }

            std::cout << "incrementing lookup counter" << std::endl;
            this->observer->observe(dns::metrics::LookupSummary::INSTANCE, builder.build());
        });

        innerHandler->on(dns::server::EventType::QUERY, [this](auto event) {
            auto builder = dns::metrics::QueryObservation::newBuilder();
            auto queryEvent = std::dynamic_pointer_cast<dns::server::QueryEvent>(event);

            builder.valid(false);
            if(auto query = queryEvent->getQuery()) {
                if(auto question = query->getQuestion()) {
                    builder.qclass(question->qclass)
                           .qname(question->qname)
                           .qtype(question->qtype)
                           .valid(true);
                }
            }

            std::cout << "incrementing query counter" << std::endl;
            this->observer->increment(dns::metrics::QueryCounter::INSTANCE, builder.build());
        });

        innerHandler->on(dns::server::EventType::REPLY, [this](auto event) {
            auto builder = dns::metrics::ReplyObservation::newBuilder();
            auto queryEvent = std::dynamic_pointer_cast<dns::server::ReplyEvent>(event);

            builder.valid(false);
            if(auto reply = queryEvent->getReply()) {
                if(auto question = reply->getQuestion()) {
                    builder.qclass(question->qclass)
                           .qname(question->qname)
                           .qtype(question->qtype)
                           .valid(true);
                }
            }

            std::cout << "incrementing reply counter" << std::endl;
            this->observer->increment(dns::metrics::ReplyCounter::INSTANCE, builder.build());
        });
    }

    std::x::expected<size_t, util::Error> ObservingHandler::handle(
            uint8_t *queryPtr, size_t querySize,
            uint8_t *replyPtr, size_t replySize) {
        return innerHandler->handle(queryPtr, querySize, replyPtr, replySize);
    }

    Handler& ObservingHandler::on(EventType eventType, util::Callback<std::shared_ptr<Event>> listener) {
        innerHandler->on(eventType, listener);
        return *this;
    }
}
