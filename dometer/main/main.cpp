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

namespace config = dometer::config;
namespace dns = dometer::dns;
namespace metrics = dometer::metrics;
using namespace std::x;

namespace dometer::main {
    void printError(std::string message, std::string details) {
        std::cerr << message << " [";
        auto multiline =  details.find('\n', 0) != std::string::npos;
        if(!multiline) {
            std::cerr << details;
        } else {
            if(details.front() != '\n')
                std::cerr << std::endl;
            size_t pos;
            std::string token;
            while((pos = details.find('\n')) != std::string::npos) {
                token = details.substr(0, pos);
                std::cerr << "  " << token << std::endl;
                details.erase(0, pos + 1);
            }
            std::cerr << "  " << details;
            if(details.back() != '\n')
                std::cerr << std::endl;
        }
        std::cerr << "]." << std::endl;
    }

    int main(int argc, char **argv) {
        auto options = dometer::main::OptionsParser::parse(argc, argv);
        if(!options) {
            printError("Invalid command line options", options.error().message);
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
            printError("Failed to load config (path: " + options->config.value() + ")", parseResults.error().message); 
            return 1;
        }
        auto config = *parseResults;

        auto observerResult = metrics::ObserverFactory::makeObserver(config.metrics);
        if(!observerResult) {
            printError("Failed to create metrics observer", observerResult.error().message);
            return 1;
        }
        auto observer = *observerResult;

        auto resolver = dns::resolver::ResolverFactory::makeResolver(config.dns.resolver);
        auto resolvingHandler = std::make_shared<dns::handler::ResolvingHandler>(resolver);
        auto observingHandler = std::make_shared<dns::handler::ObservingHandler>(resolvingHandler, observer);
        dns::server::Server server(observingHandler);
        auto serveResult = server.serve(config.dns.server.transport.bindAddress);
        if(!serveResult) {
            printError("Failed to start DNS server", serveResult.error().message);
            return 1;
        }

        return 0;
    }
}

int main(int argc, char **argv) {
    return dometer::main::main(argc, argv);
}
