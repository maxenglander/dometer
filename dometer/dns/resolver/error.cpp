#include "dometer/dns/resolver/error.hpp"
#include "dometer/util/error.hpp"

namespace dometer::dns::resolver {
    Error::Error(std::string message, ErrorCode code)
        : dometer::util::Error(message, (int)code)
    {}

    Error::Error(std::string message, ErrorCode code, dometer::util::Error cause)
        : dometer::util::Error(message, (int)code, cause)
    {}
}
