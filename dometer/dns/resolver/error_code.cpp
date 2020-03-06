#include "dometer/dns/resolver/error_code.hpp"

namespace dometer::dns::resolver {
    std::string to_string(const errorCode& errorCode) {
        switch(errorCode) {
            case errorCode::CONNREFUSED:
                return "CONNREFUSED";
            case errorCode::MSGSIZE:
                return "MSGSIZE";
            case errorCode::NOERROR:
                return "NOERROR";
            case errorCode::OTHER:
                return "OTHER";
            case errorCode::PARSEERROR:
                return "PARSEERROR";
            case errorCode::TIMEDOUT:
                return "TIMEDOUT";
        }
    }
}
