#include <iostream>
#include <memory>

#include "dometer/config/parser.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/handler/resolving_handler.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/dns/resolver/resolver_factory.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/cli/help.hpp"
#include "dometer/cli/options.hpp"
#include "dometer/cli/options_parser.hpp"
#include "dometer/event/emitter.hpp"
#include "dometer/metrics/observer.hpp"
#include "dometer/metrics/handler/handler_factory.hpp"
#include "dometer/util/error.hpp"
#include "dometer/util/error_encoder.hpp"
#include "dometer/util/human_error_encoder.hpp"

namespace config = dometer::config;
namespace dns = dometer::dns;
namespace metrics = dometer::metrics;
using namespace std::x;

namespace dometer::cli {
    int main(int argc, char **argv) {
        util::HumanErrorEncoder errorEncoder;

        auto cliOptions = dometer::cli::OptionsParser::parse(argc, argv);
        if(!cliOptions) {
            std::cerr << errorEncoder.encode(util::Error(
                "Failed to parse command line options.",
                cliOptions.error()
            ));
            return 1;
        } else if (cliOptions->help) {
            Help::printHelp();
            return 1;
        } else if (!cliOptions->config) {
            Help::printHelp();
            return 1;
        }

        auto parser = config::Parser();
        auto parseResults = parser.fromFile(cliOptions->config.value());
        if(!parseResults) {
            std::cerr << errorEncoder.encode(util::Error(
                "Failed to load configuration.",
                std::vector<std::string>{"Config file path: " + cliOptions->config.value()},
                parseResults.error()
            ));
            return 1;
        }
        auto appOptions = *parseResults;

        auto handlersResult = metrics::handler::HandlerFactory::makeHandlers(appOptions.metrics.handlers);
        if(!handlersResult) {
            std::cerr << errorEncoder.encode(util::Error(
                "Failed to create metrics handlers.",
                handlersResult.error()
            ));
            return 1;
        }
        auto observer = std::make_shared<metrics::Observer>(*handlersResult);

        auto emitter = event::Emitter<dns::event::AnyEvent>();
        auto resolver = dns::resolver::ResolverFactory::makeResolver(appOptions.dns.resolver);
        auto resolvingHandler = std::make_shared<dns::handler::ResolvingHandler>(emitter, resolver);
        dns::server::Server server(emitter, resolvingHandler);
        auto serveResult = server.serve(appOptions.dns.server.transport.bindAddress);
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
    return dometer::cli::main(argc, argv);
}
