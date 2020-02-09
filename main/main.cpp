#include <chrono>
#include <iostream>
#include <memory>

#include "config/config_parser.hpp"
#include "config/schema_validator.hpp"
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
#include "dns/server/native_resolving_handler.hpp"
#include "dns/server/query_event.hpp"
#include "dns/server/reply_event.hpp"
#include "dns/server/server.hpp"
#include "experimental/expected.hpp"
#include "metrics/observer.hpp"
#include "metrics/prometheus_handler.hpp"
#include "prometheus/exposer.h"
#include "prometheus/registry.h"

namespace config = dometer::config;
namespace dns = dometer::dns;
namespace metrics = dometer::metrics;
using namespace std::experimental;

int main(int argc, char **argv) {
    std::string configString = "{\"apiVersion\":\"v0\",\"dns\":{\"resolver\":{\"type\":\"libresolv\",\"libresolv\":{\"function\":\"search\"}},\"server\":{\"transport\":{\"bindAddress\":\"0.0.0.0:5353\",\"maxConnections\":100}}},\"metrics\":{\"handlers\":[{\"type\":\"prometheus\",\"prometheus\":{\"maxTimeSeries\":10000,\"transports\":[{\"type\":\"pull\",\"exposer\":{\"bindAddress\":\"0.0.0.0\",\"metricsPath\":\"/metrics\",\"numThreads\":2}}]}}]}}";
    auto validator = config::SchemaValidator();
    auto validation = validator.validate(configString);
    if(!validation) {
        std::cerr << "Failed to validate configuration" << std::endl;
        std::cerr << "================================" << std::endl;
        std::cerr << validation.error().message << std::endl;
        return 1;
    }
    auto parser = config::ConfigParser();
    if(parser.parse(configString)) {
        std::cout << "Successfully parsed config" << std::endl;
    }
    return 0;

    auto prometheusRegistry = std::make_shared<prometheus::Registry>();

    metrics::PrometheusHandler prometheusHandler(prometheusRegistry);

    prometheus::Exposer prometheusExposer{"0.0.0.0:9090"};
    prometheusExposer.RegisterCollectable(prometheusRegistry);

    auto serverHandler = std::make_unique<dns::server::NativeResolvingHandler>();

    serverHandler->on(dns::server::EventType::LOOKUP, [&prometheusHandler](auto event) {
        auto builder = dns::metrics::LookupObservation::newBuilder();

        auto lookupEvent = std::dynamic_pointer_cast<dns::server::LookupEvent>(event);
        auto query = lookupEvent->getQuery();

        if(query) {
            std::chrono::microseconds duration = lookupEvent->getDuration();
            std::chrono::duration<double> asSeconds
                = lookupEvent->getDuration();

            auto question = query.getQuestion();
            if(question) {
                builder.qclass(question->qclass)
                       .qname(question->qname)
                       .qtype(question->qtype)
                       .duration(asSeconds.count());
            }
        }

        prometheusHandler.observe(dns::metrics::LookupSummary::INSTANCE, builder.build());
    });

    serverHandler->on(dns::server::EventType::QUERY, [&prometheusHandler](auto event) {
        auto builder = dns::metrics::QueryObservation::newBuilder();

        auto queryEvent = std::dynamic_pointer_cast<dns::server::QueryEvent>(event);
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

        prometheusHandler.increment(dns::metrics::QueryCounter::INSTANCE, builder.build());
    });

    serverHandler->on(dns::server::EventType::REPLY, [&prometheusHandler](auto event) {
        auto builder = dns::metrics::ReplyObservation::newBuilder();

        auto queryEvent = std::dynamic_pointer_cast<dns::server::ReplyEvent>(event);
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

        prometheusHandler.increment(dns::metrics::ReplyCounter::INSTANCE, builder.build());
    });

    dns::server::Server server(std::move(serverHandler));
    auto result = server.serve();
    if(!result) {
        std::cerr << "failed to start DNS server: " + result.error().message
            + " (" + std::to_string(result.error().number) + ")" << std::endl;
        return 1;
    }

    return 0;
}
