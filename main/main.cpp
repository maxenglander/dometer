#include <iostream>
#include <memory>

#include "experimental/expected.hpp"
#include "metrics/observer.hpp"
#include "metrics/query_observation.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/server/event_type.hpp"
#include "network/dns/server/handler.hpp"
#include "network/dns/server/lookup_event.hpp"
#include "network/dns/server/native_resolving_handler.hpp"
#include "network/dns/server/query_event.hpp"
#include "network/dns/server/reply_event.hpp"
#include "network/dns/server/server.hpp"

namespace Dns = Dometer::Network::Dns;
namespace Metrics = Dometer::Metrics;
using namespace std::experimental;

int main(int argc, char **argv) {
    Metrics::Observer observer;

    std::unique_ptr<Dns::Server::Handler> handler
        = std::make_unique<Dns::Server::NativeResolvingHandler>();

    handler->on(Dns::Server::EventType::LOOKUP, [](auto event) {
        auto lookupEvent = std::dynamic_pointer_cast<Dns::Server::LookupEvent>(event);
        std::cout << "performed a lookup" << std::endl;
    });

    handler->on(Dns::Server::EventType::QUERY, [&observer](auto event) {
        std::cout << "received a query" << std::endl;
        observer.observe(Metrics::QueryObservation::newBuilder().build());
    });

    handler->on(Dns::Server::EventType::REPLY, [](auto event) {
        auto replyEvent = std::dynamic_pointer_cast<Dns::Server::ReplyEvent>(event);
        auto query = replyEvent->getQuery();
        std::cout << "sent a reply" << std::endl;
    });

    Dns::Server::Server server(std::move(handler));

    auto result = server.serve();

    if(!result) {
        std::cerr << "failed to start DNS server: " + result.error().message
            + " (" + std::to_string(result.error().number) + ")" << std::endl;
        return 1;
    }

    return 0;
}
