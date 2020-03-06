#include "dometer/dns/resolver/error.hpp"
#include "dometer/util/error.hpp"

namespace dometer::dns::resolver {
    error::error(std::string message, errorCode code)
        : dometer::util::error(message, (int)code), code(code)
    {}

    error::error(std::string message, errorCode code, dometer::util::error cause)
        : dometer::util::error(message, (int)code, cause), code(code)
    {}
}
