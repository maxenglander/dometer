#include <iostream>
#include <memory>

#include "dometer/config/parser.hpp"
#include "dometer/dns/eventmetrics/metric_recording_event_functor.hpp"
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
#include "std/x/variant.hpp"

namespace config = dometer::config;
namespace dns = dometer::dns;
namespace metrics = dometer::metrics;

namespace dometer::cli {
    int main(int argc, char **argv) {
        char myenv[] = "RESOLV_WRAPPER_HOSTS=/tmp/fakehosts";
        putenv(myenv);

        util::human_error_encoder error_encoder;

        auto cli_options = dometer::cli::options_parser::parse(argc, argv);
        if(!cli_options) {
            std::cerr << error_encoder.encode(util::error(
                "Failed to parse command line options.",
                cli_options.error()
            ));
            return 1;
        } else if (cli_options->help) {
            help::print_help();
            return 1;
        } else if (!cli_options->config) {
            help::print_help();
            return 1;
        }

        auto parser = config::parser();
        auto parse_results = parser.from_file(cli_options->config.value());
        if(!parse_results) {
            std::cerr << error_encoder.encode(util::error(
                "Failed to load configuration.",
                std::vector<std::string>{"Config file path: " + cli_options->config.value()},
                parse_results.error()
            ));
            return 1;
        }
        auto app_options = *parse_results;

        auto handlers_result = metrics::handler::handler_factory::make_handlers(app_options.metrics.handlers);
        if(!handlers_result) {
            std::cerr << error_encoder.encode(util::error(
                "Failed to create metrics handlers.",
                handlers_result.error()
            ));
            return 1;
        }
        auto observer = std::make_shared<metrics::observer>(*handlers_result);
        auto emitter = event::emitter<dns::event::any_event>();
        auto metric_recording_event_functor = dometer::dns::eventmetrics::metric_recording_event_functor(observer);
        emitter.on([&metric_recording_event_functor](dns::event::any_event event) {
            metric_recording_event_functor(event);
        });

        auto resolver = dns::resolver::resolver_factory::make_resolver(app_options.dns.resolver);
        auto resolving_handler = std::make_shared<dns::handler::resolving_handler>(emitter, resolver);
        dns::server::server server(emitter, resolving_handler);
        auto start_result = server.start(app_options.dns.server.transport.bind_address);
        if(!start_result) {
            std::cerr << error_encoder.encode(util::error(
                "Failed to start DNS server",
                start_result.error()
            ));
            return 1;
        }
        server.join();

        return 0;
    }
}

int main(int argc, char **argv) {
    return dometer::cli::main(argc, argv);
}
