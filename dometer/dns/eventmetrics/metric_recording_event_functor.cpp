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
        std::cout << "copy-constructed functor" << std::endl;
    }

    MetricRecordingEventFunctor::~MetricRecordingEventFunctor() {
        std::cout << "destroying functor" << std::endl;
    }


    void MetricRecordingEventFunctor::operator() (dometer::dns::event::AnyEvent anyEvent) {
        std::x::visit(std::x::overloaded(
            [&](const dometer::dns::event::ParseQueryEvent parseQueryEvent) {
                const uint64_t sessionId = parseQueryEvent.getSessionId();
                auto search = this->sessions.find(sessionId);
                std::cout << "handling parse query event; checking for session = " << std::to_string(sessionId) << std::endl;
                if(search != this->sessions.end()) {
                    std::cout << "session exists, adding parse query event" << std::endl;
                    search->second.setParseQueryEvent(parseQueryEvent);
                }
            },

            [&](const dometer::dns::event::ParseReplyEvent parseReplyEvent) {
                const uint64_t sessionId = parseReplyEvent.getSessionId();
                std::cout << "handling parse reply event; checking for session = " << std::to_string(sessionId) << std::endl;
                auto search = this->sessions.find(sessionId);
                if(search != this->sessions.end()) {
                    std::cout << "session exists, adding parse reply event" << std::endl;
                    search->second.setParseReplyEvent(parseReplyEvent);
                }
            },

            [&](const dometer::dns::event::ResolveQueryEvent resolveQueryEvent) {
                const uint64_t sessionId = resolveQueryEvent.getSessionId();
                std::cout << "handling resolve query event; checking for session = " << std::to_string(sessionId) << std::endl;
                auto search = this->sessions.find(sessionId);
                if(search != this->sessions.end()) {
                    std::cout << "session exists, adding resolve query event" << std::endl;
                    search->second.setResolveQueryEvent(resolveQueryEvent);
                }
            },

            [&](const dometer::dns::event::StartSessionEvent startSessionEvent) {
                std::cout << "creating new dns session" << std::endl;
                this->sessions.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple<uint64_t>(startSessionEvent.getSessionId()),
                    std::forward_as_tuple<uint64_t>(startSessionEvent.getSessionId())
                );
                std::cout << "created new dns session, total sessions = " << std::to_string(this->sessions.size()) << std::endl;
            },

            [&](const dometer::dns::event::StopSessionEvent stopSessionEvent) {
                std::cout << "stopping dns session, total sessions = " << std::to_string(this->sessions.size()) << std::endl;

                const uint64_t sessionId = stopSessionEvent.getSessionId();

                auto search = this->sessions.find(sessionId);
                std::cout << "checking whether session exists: " << std::to_string(sessionId) << std::endl;
                if(search != this->sessions.end()) {
                    auto session = search->second;
                    std::cout << "session exists, checking for resolve query event" << std::endl;
                    auto resolveQueryEvent = session.getResolveQueryEvent();
                    if(resolveQueryEvent) {
                        std::cout << "resolve query event exists, building lookup observation" << std::endl;
                        auto builder = dometer::dns::metrics::LookupObservation::newBuilder();
                        auto parseQueryEvent = session.getParseQueryEvent();
                        auto parseReplyEvent = session.getParseReplyEvent();

                        if(!parseQueryEvent) {
                            std::cerr << "parse query event unexpectedly absent" << std::endl;
                        } else {
                            std::cerr << "parse query event is present" << std::endl;
                        }

                        std::cout << "getting query" << std::endl;
                        auto query = parseQueryEvent->getMessage();
                        std::cout << "got query; getting question" << std::endl;
                        auto question = query->getQuestion();
                        std::cout << "got question; getting resolution" << std::endl;
                        auto resolution = resolveQueryEvent->getResolution();
                        std::cout << "got resolution; setting duration" << std::endl;
                        builder.duration(resolveQueryEvent->getDuration().count());
                        builder.error("-");
                        builder.qclass(question->qclass);
                        builder.qname(question->qname);
                        builder.qtype(question->qtype);
                        builder.rcode("-");

                        if(resolution) {
                            auto reply = session.getParseReplyEvent()->getMessage();
                            builder.rcode(reply->getRCode());
                        } else {
                            builder.error(dometer::dns::resolver::to_string(resolution.error().code));
                        }


                        this->observer->observe(dometer::dns::metrics::LookupSummary::INSTANCE, builder.build());
                    }
                }

                this->sessions.erase(sessionId);
            }
        ), anyEvent);
    }
}
