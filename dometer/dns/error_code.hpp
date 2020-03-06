#pragma once

#include <stdint.h>
#include <string>

namespace dometer::dns {
    class errorCode {
        public:
            static const errorCode NOERROR;
            static const errorCode CONNREFUSED;
            static const errorCode TIMEDOUT;

            errorCode(uint8_t value);
            operator uint8_t() const;
            operator std::string() const;
        private:
            uint8_t value;
    };
}
