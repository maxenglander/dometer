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
    MetricRecordingEventFunctor::MetricRecordingEventFunctor(std::shared_ptr<dometer::metrics::Observer> observer)
        : observer(observer) 
    {}

    MetricRecordingEventFunctor::MetricRecordingEventFunctor(const MetricRecordingEventFunctor& functor)
        : observer(functor.observer),
          sessions(functor.sessions)
    {
    }

    MetricRecordingEventFunctor::~MetricRecordingEventFunctor() {
    }

    void MetricRecordingEventFunctor::operator() (dometer::dns::event::AnyEvent anyEvent) {
        std::x::visit(std::x::overloaded(
            [&](const dometer::dns::event::ParseQueryEvent parseQueryEvent) {
                const uint64_t sessionId = parseQueryEvent.getSessionId();
                auto search = this->sessions.find(sessionId);
                if(search == this->sessions.end()) return;
                search->second.setParseQueryEvent(parseQueryEvent);
            },

            [&](const dometer::dns::event::ParseReplyEvent parseReplyEvent) {
                const uint64_t sessionId = parseReplyEvent.getSessionId();
                auto search = this->sessions.find(sessionId);
                if(search == this->sessions.end()) return;
                search->second.setParseReplyEvent(parseReplyEvent);
            },

            [&](const dometer::dns::event::ResolveQueryEvent resolveQueryEvent) {
                const uint64_t sessionId = resolveQueryEvent.getSessionId();
                auto search = this->sessions.find(sessionId);
                if(search == this->sessions.end()) return;
                search->second.setResolveQueryEvent(resolveQueryEvent);
            },

            [&](const dometer::dns::event::StartSessionEvent startSessionEvent) {
                this->sessions.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple<uint64_t>(startSessionEvent.getSessionId()),
                    std::forward_as_tuple<uint64_t>(startSessionEvent.getSessionId())
                );
            },

            [&](const dometer::dns::event::StopSessionEvent stopSessionEvent) {
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
                    if(auto reply = parseReplyEvent->getMessage()) {
                        builder.rcode(reply->getRCode());
                    }
                }

                this->observer->observe(dometer::dns::metrics::LookupSummary::INSTANCE, builder.build());
            }
        ), anyEvent);
    }
}
