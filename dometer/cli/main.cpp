#include <iostream>
#include <memory>
#include <utility>

#include "dometer/app/app_factory.hpp"
#include "dometer/config/parser.hpp"
#include "dometer/dns/eventmetrics/metric_recording_callback.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/handler/resolving_handler.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/dns/resolver/resolver_factory.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/cli/help.hpp"
#include "dometer/cli/options.hpp"
#include "dometer/cli/options_parser.hpp"
#include "dometer/event/emitter.hpp"
#include "dometer/metrics/recorder.hpp"
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

        auto app_result = dometer::app::app_factory::make_app(app_options);
        if(!app_result) {
            std::cerr << error_encoder.encode(util::error(
                "Failed to start create app.",
                app_result.error()
            ));
            return 1;

        }
        auto app = *app_result;

        auto start_result = app->start();
        if(!start_result) {
            std::cerr << error_encoder.encode(util::error(
                "Failed to start DNS server",
                start_result.error()
            ));
            return 1;
        }

        app->join();

        return 0;

        /**
        auto handlers_result = metrics::handler::handler_factory::make_handlers(app_options.metrics.handlers);
        if(!handlers_result) {
            std::cerr << error_encoder.encode(util::error(
                "Failed to create metrics handlers.",
                handlers_result.error()
            ));
            return 1;
        }
        auto recordr = std::make_shared<metrics::recorder>(std::move(*handlers_result));
        auto emitter = std::make_shared<event::emitter<dns::event::any_event>>();
        auto metric_recording_callback = dometer::dns::eventmetrics::metric_recording_callback(recordr);
        emitter->on([&metric_recording_callback](dns::event::any_event event) {
            metric_recording_callback(event);
        });

        auto resolver_result = dns::resolver::resolver_factory::make_resolver(app_options.dns.resolver);
        if(!resolver_result) {
            std::cerr << error_encoder.encode(util::error(
                "Failed to create resolver.",
                resolver_result.error()
            ));
            return 1;
        }
        auto resolving_handler = std::make_shared<dns::handler::resolving_handler>(emitter, *resolver_result);
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
        */

        return 0;
    }
}

int main(int argc, char **argv) {
    return dometer::cli::main(argc, argv);
}
