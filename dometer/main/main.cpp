#include <iostream>
#include <memory>

#include "dometer/config/config_parser.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/dns/resolver/resolver_factory.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/handler/observing_handler.hpp"
#include "dometer/dns/handler/resolving_handler.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/main/help.hpp"
#include "dometer/main/options.hpp"
#include "dometer/main/options_parser.hpp"
#include "dometer/metrics/observer.hpp"
#include "dometer/metrics/observer_factory.hpp"
#include "dometer/util/error.hpp"
#include "dometer/util/error_encoder.hpp"
#include "dometer/util/human_error_encoder.hpp"

namespace config = dometer::config;
namespace dns = dometer::dns;
namespace metrics = dometer::metrics;
using namespace std::x;

namespace dometer::main {
    int main(int argc, char **argv) {
        util::HumanErrorEncoder errorEncoder;

        auto options = dometer::main::OptionsParser::parse(argc, argv);
        if(!options) {
            std::cerr << errorEncoder.encode(util::Error(
                "Failed to parse command line options.",
                options.error()
            ));
            return 1;
        } else if (options->help) {
            Help::printHelp();
            return 1;
        } else if (!options->config) {
            Help::printHelp();
            return 1;
        }

        auto parser = config::ConfigParser();
        auto parseResults = parser.fromFile(options->config.value());
        if(!parseResults) {
            std::cerr << errorEncoder.encode(util::Error(
                "Failed to load configuration.",
                std::vector<std::string>{"Config file path: " + options->config.value()},
                parseResults.error()
            ));
            return 1;
        }
        auto config = *parseResults;

        auto observerResult = metrics::ObserverFactory::makeObserver(config.metrics);
        if(!observerResult) {
            std::cerr << errorEncoder.encode(util::Error(
                "Failed to create metrics observer.",
                observerResult.error())
            );
            return 1;
        }
        auto observer = *observerResult;

        auto resolver = dns::resolver::ResolverFactory::makeResolver(config.dns.resolver);
        auto resolvingHandler = std::make_shared<dns::handler::ResolvingHandler>(resolver);
        auto observingHandler = std::make_shared<dns::handler::ObservingHandler>(resolvingHandler, observer);
        dns::server::Server server(observingHandler);
        auto serveResult = server.serve(config.dns.server.transport.bindAddress);
        if(!serveResult) {
            std::cerr << errorEncoder.encode(util::Error(
                "Failed to start DNS server",
                serveResult.error()
            ));
            return 1;
        }

        return 0;
    }
}

int main(int argc, char **argv) {
    return dometer::main::main(argc, argv);
}
