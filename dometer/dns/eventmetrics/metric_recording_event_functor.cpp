#include <iostream>
#include <memory>
#include <utility>
#include <tuple>

#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/event/parse_query_event.hpp"
#include "dometer/dns/event/parse_reply_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/event/start_session_event.hpp"
#include "dometer/dns/event/stop_session_event.hpp"
#include "dometer/dns/eventmetrics/metric_recording_event_functor.hpp"
#include "dometer/dns/metrics/lookup_observation.hpp"
#include "dometer/dns/metrics/lookup_summary.hpp"
#include "dometer/dns/resolver/error_code.hpp"
#include "dometer/metrics/observer.hpp"
#include "std/x/variant.hpp"

namespace dometer::dns::eventmetrics {
    metric_recording_event_functor::metric_recording_event_functor(std::shared_ptr<dometer::metrics::observer> observer)
        : observer(observer) 
    {}

    metric_recording_event_functor::metric_recording_event_functor(const metric_recording_event_functor& functor)
        : observer(functor.observer),
          sessions(functor.sessions)
    {
    }

    metric_recording_event_functor::~metric_recording_event_functor() {
    }

    void metric_recording_event_functor::operator() (dometer::dns::event::any_event anyEvent) {
        std::x::visit(std::x::overloaded(
            [&](const dometer::dns::event::parse_query_event parseQueryEvent) {
                const uint64_t sessionId = parseQueryEvent.get_session_id();
                auto search = this->sessions.find(sessionId);
                if(search == this->sessions.end()) return;
                search->second.setParseQueryEvent(parseQueryEvent);
            },

            [&](const dometer::dns::event::parse_reply_event parseReplyEvent) {
                const uint64_t sessionId = parseReplyEvent.get_session_id();
                auto search = this->sessions.find(sessionId);
                if(search == this->sessions.end()) return;
                search->second.setParseReplyEvent(parseReplyEvent);
            },

            [&](const dometer::dns::event::resolve_query_event resolveQueryEvent) {
                const uint64_t sessionId = resolveQueryEvent.getSessionId();
                auto search = this->sessions.find(sessionId);
                if(search == this->sessions.end()) return;
                search->second.setResolveQueryEvent(resolveQueryEvent);
            },

            [&](const dometer::dns::event::start_session_event startSessionEvent) {
                this->sessions.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple<uint64_t>(startSessionEvent.getSessionId()),
                    std::forward_as_tuple<uint64_t>(startSessionEvent.getSessionId())
                );
            },

            [&](const dometer::dns::event::stop_session_event stopSessionEvent) {
                auto search = this->sessions.find(stopSessionEvent.getSessionId());
                if(search == this->sessions.end()) return;

                auto session = search->second;
                this->sessions.erase(stopSessionEvent.getSessionId());

                if(!session.getResolveQueryEvent()) return;
                auto resolveQueryEvent = session.getResolveQueryEvent();

                auto builder = dometer::dns::metrics::LookupObservation::newBuilder();

                auto question = resolveQueryEvent->getQuestion();
                builder.qclass(question.qclass)
                       .qname(question.qname)
                       .qtype(question.qtype);

                auto resolution = resolveQueryEvent->getResolution();
                builder.duration(resolveQueryEvent->getDuration().count());

                builder.error("-");
                builder.rcode("-");
                if(!resolution) {
                    builder.error(dometer::dns::resolver::to_string(resolution.error().code));
                } else if(auto parseReplyEvent = session.getParseReplyEvent()) {
                    if(auto reply = parseReplyEvent->get_message()) {
                        builder.rcode(reply->getRCode());
                    }
                }

                this->observer->observe(dometer::dns::metrics::LookupSummary::INSTANCE, builder.build());
            }
        ), anyEvent);
    }
}
