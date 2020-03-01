#pragma once

#include <stdint.h>
#include <string>

namespace dometer::dns {
    class ErrorCode {
        public:
            static const ErrorCode NOERROR;
            static const ErrorCode CONNREFUSED;
            static const ErrorCode TIMEDOUT;

            ErrorCode(uint8_t value);
            operator uint8_t() const;
            operator std::string() const;
        private:
            uint8_t value;
    };
}
