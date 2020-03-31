#include <iostream>

#include "dometer/app/app_factory.hpp"
#include "dometer/config/parser.hpp"
#include "dometer/cli/help.hpp"
#include "dometer/cli/options.hpp"
#include "dometer/cli/options_parser.hpp"
#include "dometer/util/error.hpp"
#include "dometer/util/human_error_encoder.hpp"

namespace config = dometer::config;
namespace dns = dometer::dns;
namespace metrics = dometer::metrics;

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
        dometer::cli::help::print_help();
        return 1;
    } else if (!cli_options->config) {
        dometer::cli::help::print_help();
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

    auto start_result = app->start(app_options.dns.server.transport.bind_address);
    if(!start_result) {
        std::cerr << error_encoder.encode(util::error(
            "Failed to start DNS server",
            start_result.error()
        ));
        return 1;
    }

    app->join();

    return 0;
}
