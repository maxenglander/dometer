#pragma once

#include "dometer/dns/resolver/error_code.hpp"
#include "dometer/util/error.hpp"

namespace dometer::dns::resolver {
    struct Error : public dometer::util::Error {
        Error(std::string, ErrorCode);
        Error(std::string, ErrorCode, dometer::util::Error);

        const ErrorCode code;
    };
}
