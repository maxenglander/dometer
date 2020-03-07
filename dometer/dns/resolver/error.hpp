#pragma once

#include "dometer/dns/resolver/error_code.hpp"
#include "dometer/util/error.hpp"

namespace dometer::dns::resolver {
    struct error : public dometer::util::error {
        error(std::string, error_code);
        error(std::string, error_code, dometer::util::error);

        const error_code code;
    };
}
