#include "dometer/dns/resolver/error_code.hpp"

namespace dometer::dns::resolver {
    std::string to_string(const error_code& error_code) {
        switch(error_code) {
            case error_code::connrefused:
                return "CONNREFUSED";
            case error_code::msgsize:
                return "MSGSIZE";
            case error_code::noerror:
                return "NOERROR";
            case error_code::other:
                return "OTHER";
            case error_code::parseerror:
                return "PARSEERROR";
            case error_code::timedout:
                return "TIMEDOUT";
        }
    }
}
