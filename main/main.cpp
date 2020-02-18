#include <chrono>
#include <iostream>
#include <memory>

#include "config/config_parser.hpp"
#include "dns/packet.hpp"
#include "dns/metrics/lookup_observation.hpp"
#include "dns/metrics/lookup_summary.hpp"
#include "dns/metrics/query_counter.hpp"
#include "dns/metrics/query_observation.hpp"
#include "dns/metrics/reply_counter.hpp"
#include "dns/metrics/reply_observation.hpp"
#include "dns/resolver/resolver.hpp"
#include "dns/resolver/resolver_factory.hpp"
#include "dns/resolver/libresolv_function.hpp"
#include "dns/resolver/libresolv_resolver.hpp"
#include "dns/server/event_type.hpp"
#include "dns/server/handler.hpp"
#include "dns/server/lookup_event.hpp"
#include "dns/server/observing_handler.hpp"
#include "dns/server/query_event.hpp"
#include "dns/server/reply_event.hpp"
#include "dns/server/resolving_handler.hpp"
#include "dns/server/server.hpp"
#include "metrics/observer.hpp"
#include "metrics/observer_factory.hpp"

namespace config = dometer::config;
namespace dns = dometer::dns;
namespace metrics = dometer::metrics;
using namespace std::x;

int main(int argc, char **argv) {
    std::string configString = "{\"apiVersion\":\"v0\",\"dns\":{\"resolver\":{\"type\":\"libresolv\",\"libresolv\":{\"function\":\"search\"}},\"server\":{\"transport\":{\"bindAddress\":\"0.0.0.0:5353\"}}},\"metrics\":{\"handlers\":[{\"type\":\"prometheus\",\"prometheus\":{\"maxTimeSeries\":20000,\"transports\":[{\"type\":\"pull\",\"exposer\":{\"bindAddress\":\"0.0.0.0:9090\",\"metricsPath\":\"/metrics\",\"numThreads\":2}}]}}]}}";
    auto parser = config::ConfigParser();
    auto parseResults = parser.parse(configString);
    if(!parseResults) {
        std::cerr << "Failed to parse configuration" << std::endl;
        std::cerr << "=============================" << std::endl;
        std::cerr << parseResults.error().message << std::endl;
        return 1;
    }
    auto config = *parseResults;

    auto observer = metrics::ObserverFactory::makeObserver(config.metrics);
    auto resolver = dns::resolver::ResolverFactory::makeResolver(config.dns.resolver);
    auto resolvingHandler = std::make_shared<dns::server::ResolvingHandler>(resolver);
    auto observingHandler = std::make_shared<dns::server::ObservingHandler>(resolvingHandler, observer);
    dns::server::Server server(observingHandler);

    auto result = server.serve(config.dns.server.transport.bindAddress);
    if(!result) {
        std::cerr << "Failed to start DNS server [" + result.error().message + "]" << std::endl;
        return 1;
    }

    return 0;
}
