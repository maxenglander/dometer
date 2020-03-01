#include "dometer/dns/resolver/error_code.hpp"

namespace dometer::dns::resolver {
    std::string to_string(const ErrorCode& errorCode) {
        switch(errorCode) {
            case ErrorCode::CONNREFUSED:
                return "CONNREFUSED";
            case ErrorCode::MSGSIZE:
                return "MSGSIZE";
            case ErrorCode::NOERROR:
                return "NOERROR";
            case ErrorCode::OTHER:
                return "OTHER";
            case ErrorCode::PARSEERROR:
                return "PARSEERROR";
            case ErrorCode::TIMEDOUT:
                return "TIMEDOUT";
        }
    }
}
