#include <getopt.h>
#include <iostream>
#include <string>

#include "main/options.hpp"
#include "main/options_parser.hpp"
#include "util/error.hpp"
#include "x/expected.hpp"

namespace util = dometer::util;

namespace dometer::main {
    std::x::expected<Options, util::Error> OptionsParser::parse(int argc, char** argv) {
        const option longOptions[] = {
            {"config", required_argument, nullptr, 'c'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
        };
        const char* const shortOptions = "";

        std::string config = "";
        bool help = false;

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
                    config = std::string(optarg);
                    break;
                case 'h':
                    help = true;
                    break;
                case '?': // Missing or ambiguous argument
                    if(optopt == 'c') {
                        return std::x::unexpected<util::Error>(util::Error{
                            "--config requires an argument"
                        });
                    } else {
                        return std::x::unexpected<util::Error>(util::Error{
                            "unrecognized option: " + std::string(argv[optind - 1])
                        });
                    }
                default:
                    return Options{
                        config,
                        true
                    };
            }
        }

        return Options{
            config,
            help
        };
    }
}
