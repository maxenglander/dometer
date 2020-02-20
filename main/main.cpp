#include <iostream>
#include <memory>

#include "config/config_parser.hpp"
#include "dns/resolver/resolver.hpp"
#include "dns/resolver/resolver_factory.hpp"
#include "dns/handler/handler.hpp"
#include "dns/handler/observing_handler.hpp"
#include "dns/handler/resolving_handler.hpp"
#include "dns/server/server.hpp"
#include "main/options.hpp"
#include "main/options_parser.hpp"
#include "metrics/observer.hpp"
#include "metrics/observer_factory.hpp"

namespace config = dometer::config;
namespace dns = dometer::dns;
namespace metrics = dometer::metrics;
using namespace std::x;

int main(int argc, char **argv) {
    auto options = dometer::main::OptionsParser::parse(argc, argv);
    if(!options) {
        std::cerr << "Failed to parse command-line options" << std::endl;
        std::cerr << "====================================" << std::endl;
        std::cerr << options.error().message << std::endl;
        return 1;
    } else {
        std::cout << "Command-line options" << std::endl;
        std::cerr << "====================================" << std::endl;
        std::cout << "config=" << options->config << std::endl;
        std::cout << "help=" << options->help << std::endl;
    }

    auto parser = config::ConfigParser();
    auto parseResults = parser.fromFile(options->config);
    if(!parseResults) {
        std::cerr << "Failed to parse configuration" << std::endl;
        std::cerr << "====================================" << std::endl;
        std::cerr << parseResults.error().message << std::endl;
        return 1;
    }

    auto config = *parseResults;

    auto observer = metrics::ObserverFactory::makeObserver(config.metrics);
    auto resolver = dns::resolver::ResolverFactory::makeResolver(config.dns.resolver);
    auto resolvingHandler = std::make_shared<dns::handler::ResolvingHandler>(resolver);
    auto observingHandler = std::make_shared<dns::handler::ObservingHandler>(resolvingHandler, observer);
    dns::server::Server server(observingHandler);

    auto result = server.serve(config.dns.server.transport.bindAddress);
    if(!result) {
        std::cerr << "Failed to start DNS server [" + result.error().message + "]" << std::endl;
        return 1;
    }

    return 0;
}
