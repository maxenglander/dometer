#include "dometer/dns/handler/error.hpp"
#include "dometer/util/error.hpp"

namespace dometer::dns::handler {
    error::error(std::string message, error_code code)
        : dometer::util::error(message, (int)code), code(code)
    {}

    error::error(std::string message, error_code code, dometer::util::error cause)
        : dometer::util::error(message, (int)code, cause), code(code)
    {}
}
