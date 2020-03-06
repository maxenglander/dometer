#include <getopt.h>
#include <iostream>
#include <string>

#include "dometer/cli/options.hpp"
#include "dometer/cli/options_parser.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::cli {
    std::x::expected<Options, util::error> options_parser::parse(int argc, char** argv) {
        const option longOptions[] = {
            {"config", required_argument, nullptr, 'c'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
        };
        const char* const shortOptions = "";

        Options options{
            std::x::nullopt,
            false
        };

        opterr = 0;
        while(true) {
            int optionIndex = 0; 
            const auto option = getopt_long(argc, argv, shortOptions, longOptions, &optionIndex);

            if(option == -1) {
                // No more arguments
                break;
            }
            
            switch(option) {
                case 'c':
                    options.config.emplace(std::string(optarg));
                    break;
                case 'h':
                    options.help = true;
                    break;
                case '?': // Missing or ambiguous argument
                    if(optopt == 'c') {
                        return std::x::unexpected<util::error>(util::error(
                            "A specifed option was provided without a required argument.",
                            std::vector<std::string>{
                              "Specified option: --config",
                              "Required argument: <path>"
                            }
                        ));
                    } else {
                        return std::x::unexpected<util::error>(util::error(
                            "A provided option is not recognized (" + std::string(argv[optind - 1]) + ")."
                        ));
                    }
                default:
                    options.config = "";
                    options.help = true;
            }
        }

        return options;
    }
}
