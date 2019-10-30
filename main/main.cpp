#include <iostream>
#include <memory>

#include "dns/packet.hpp"
#include "dns/metrics/lookup_observation.hpp"
#include "dns/metrics/query_observation.hpp"
#include "dns/metrics/reply_observation.hpp"
#include "dns/server/event_type.hpp"
#include "dns/server/handler.hpp"
#include "dns/server/lookup_event.hpp"
#include "dns/server/native_resolving_handler.hpp"
#include "dns/server/query_event.hpp"
#include "dns/server/reply_event.hpp"
#include "dns/server/server.hpp"
#include "experimental/expected.hpp"
#include "metrics/observer.hpp"
#include "metrics/prometheus_handler.hpp"

#include "prometheus/exposer.h"
#include "prometheus/registry.h"

namespace Dns = Dometer::Dns;
namespace Metrics = Dometer::Metrics;
using namespace std::experimental;

int main(int argc, char **argv) {
    auto prometheusRegistry = std::make_shared<prometheus::Registry>();

    auto prometheusHandler = std::make_shared<Metrics::PrometheusHandler>(prometheusRegistry);
    Metrics::Observer<Metrics::PrometheusHandler> metricsObserver(prometheusHandler);

    prometheus::Exposer prometheusExposer{"0.0.0.0:9090"};
    prometheusExposer.RegisterCollectable(prometheusRegistry);

    auto serverHandler = std::make_unique<Dns::Server::NativeResolvingHandler>();

    serverHandler->on(Dns::Server::EventType::LOOKUP, [&metricsObserver](auto event) {
        auto builder = Dns::Metrics::LookupObservation::newBuilder();

        auto lookupEvent = std::dynamic_pointer_cast<Dns::Server::LookupEvent>(event);
        auto query = lookupEvent->getQuery();

        if(query) {
            auto question = query.getQuestion();
            if(question) {
                builder.qclass(question->qclass)
                       .qname(question->qname)
                       .qtype(question->qtype)
                       .duration(lookupEvent->getDuration().count());
            }
        }

        metricsObserver.observe(builder.build());
    });

    serverHandler->on(Dns::Server::EventType::QUERY, [&metricsObserver](auto event) {
        auto builder = Dns::Metrics::QueryObservation::newBuilder();

        auto queryEvent = std::dynamic_pointer_cast<Dns::Server::QueryEvent>(event);
        auto query = queryEvent->getQuery();

        builder.valid(false);
        if(query) {
            auto question = query->getQuestion();
            if(question) {
                builder.qclass(question->qclass)
                       .qname(question->qname)
                       .qtype(question->qtype)
                       .valid(true);
            }
        }

        metricsObserver.observe(builder.build());
    });

    serverHandler->on(Dns::Server::EventType::REPLY, [&metricsObserver](auto event) {
        auto builder = Dns::Metrics::ReplyObservation::newBuilder();

        auto queryEvent = std::dynamic_pointer_cast<Dns::Server::ReplyEvent>(event);
        auto reply = queryEvent->getReply();

        builder.valid(false);
        if(reply) {
            auto question = reply->getQuestion();
            if(question) {
                builder.qclass(question->qclass)
                       .qname(question->qname)
                       .qtype(question->qtype)
                       .valid(true);
            }
        }

        metricsObserver.observe(builder.build());
    });

    Dns::Server::Server server(std::move(serverHandler));
    auto result = server.serve();
    if(!result) {
        std::cerr << "failed to start DNS server: " + result.error().message
            + " (" + std::to_string(result.error().number) + ")" << std::endl;
        return 1;
    }

    return 0;
}
