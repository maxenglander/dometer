#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <tuple>

#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/event/parse_query_event.hpp"
#include "dometer/dns/event/parse_reply_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/event/start_session_event.hpp"
#include "dometer/dns/event/stop_session_event.hpp"
#include "dometer/dns/eventmetrics/metric_recording_callback.hpp"
#include "dometer/dns/metrics/lookup_histogram.hpp"
#include "dometer/dns/metrics/lookup_observation_builder.hpp"
#include "dometer/dns/resolver/error_code.hpp"
#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/recorder.hpp"
#include "std/x/variant.hpp"

namespace dometer::dns::eventmetrics {
    metric_recording_callback::metric_recording_callback(std::shared_ptr<dometer::metrics::recorder> recorder)
        : recorder(recorder),
          sessions()
    {}

    metric_recording_callback::metric_recording_callback(metric_recording_callback&& src)
        : recorder(src.recorder),
          sessions(src.sessions)
    {}

    void metric_recording_callback::operator() (dometer::dns::event::any_event any_event) {
        std::x::visit(std::x::overloaded(
            [&](const dometer::dns::event::parse_query_event parse_query_event) {
                const uint64_t session_id = parse_query_event.get_session_id();
                auto search = this->sessions.find(session_id);
                if(search == this->sessions.end()) return;
                search->second.set_parse_query_event(parse_query_event);
            },

            [&](const dometer::dns::event::parse_reply_event parse_reply_event) {
                const uint64_t session_id = parse_reply_event.get_session_id();
                auto search = this->sessions.find(session_id);
                if(search == this->sessions.end()) return;
                search->second.set_parse_reply_event(parse_reply_event);
            },

            [&](const dometer::dns::event::resolve_query_event resolve_query_event) {
                const uint64_t session_id = resolve_query_event.get_session_id();
                auto search = this->sessions.find(session_id);
                if(search == this->sessions.end()) return;
                search->second.set_resolve_query_event(resolve_query_event);
            },

            [&](const dometer::dns::event::start_session_event start_session_event) {
                sessions.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple<uint64_t>(start_session_event.get_session_id()),
                    std::forward_as_tuple<uint64_t>(start_session_event.get_session_id())
                );
            },

            [&](const dometer::dns::event::stop_session_event stop_session_event) {
                auto search = this->sessions.find(stop_session_event.get_session_id());
                if(search == this->sessions.end()) return;

                auto session = search->second;
                this->sessions.erase(stop_session_event.get_session_id());

                if(!session.get_resolve_query_event()) return;
                auto resolve_query_event = session.get_resolve_query_event();

                std::map<std::string, std::string> labels;
                dometer::dns::metrics::lookup_observation_builder lookup_observation_builder;

                auto question = resolve_query_event->get_question();
                lookup_observation_builder.qclass(question.qclass).qname(question.qname).qtype(question.qtype);

                auto resolution = resolve_query_event->get_resolution();
                if(!resolution) {
                    lookup_observation_builder.error(resolution.error());
                } else if(auto parse_reply_event = session.get_parse_reply_event()) {
                    if(auto reply = parse_reply_event->get_message()) {
                        lookup_observation_builder.rcode(reply->get_rcode());
                    }
                }

                lookup_observation_builder.duration(resolve_query_event->get_duration(),
                                                    dometer::dns::metrics::lookup_histogram::instance.unit);

                auto observation = lookup_observation_builder.build();

                this->recorder->record(dometer::dns::metrics::lookup_histogram::instance,
                                       observation.labels,
                                       observation.value);
            }
        ), any_event);
    }
}
