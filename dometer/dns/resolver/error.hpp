#pragma once

#include "dometer/dns/resolver/error_code.hpp"
#include "dometer/util/error.hpp"

namespace dometer::dns::resolver {
    struct error : public dometer::util::error {
        error(std::string, errorCode);
        error(std::string, errorCode, dometer::util::error);

        const errorCode code;
    };
}
