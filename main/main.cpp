#include <iostream>
#include <memory>

#include "dns/packet.hpp"
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
#include "metrics/query_observation.hpp"

namespace Dns = Dometer::Dns;
namespace Metrics = Dometer::Metrics;
using namespace std::experimental;

int main(int argc, char **argv) {
    Metrics::PrometheusHandler prometheusHandler;
    Metrics::Observer metricsObserver(prometheusHandler);

    std::unique_ptr<Dns::Server::Handler> serverHandler
        = std::make_unique<Dns::Server::NativeResolvingHandler>();

    serverHandler->on(Dns::Server::EventType::LOOKUP, [](auto event) {
        auto lookupEvent = std::dynamic_pointer_cast<Dns::Server::LookupEvent>(event);
        std::cout << "performed a lookup" << std::endl;
    });

    serverHandler->on(Dns::Server::EventType::QUERY, [&metricsObserver](auto event) {
        Metrics::QueryObservation::Builder builder = Metrics::QueryObservation::newBuilder();

        std::cout << "received a query" << std::endl;
        auto queryEvent = std::dynamic_pointer_cast<Dns::Server::QueryEvent>(event);
        auto query = queryEvent->getQuery();

        builder.valid(false);
        if(query) {
            auto question = query->getQuestion();
            if(question) {
                builder.qname(question->qname);
                builder.valid(true);
            }
        }

        metricsObserver.observe(builder.build());
    });

    serverHandler->on(Dns::Server::EventType::REPLY, [](auto event) {
        auto replyEvent = std::dynamic_pointer_cast<Dns::Server::ReplyEvent>(event);
        auto query = replyEvent->getQuery();
        std::cout << "sent a reply" << std::endl;
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
