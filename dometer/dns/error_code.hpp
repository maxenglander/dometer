#pragma once

#include <stdint.h>
#include <string>

namespace dometer::dns {
    class error_code {
        public:
            static const error_code noerror;
            static const error_code connrefused;
            static const error_code timedout;

            error_code(uint8_t value);
            operator uint8_t() const;
            operator std::string() const;
        private:
            uint8_t value;
    };
}
