#pragma once

#include "dometer/dns/handler/error_code.hpp"
#include "dometer/util/error.hpp"

namespace dometer::dns::handler {
    struct error : public dometer::util::error {
        error(std::string, error_code);
        error(std::string, error_code, dometer::util::error);

        const error_code code;
    };
}
