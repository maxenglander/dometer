#pragma once

#include <stdint.h>
#include <string>

namespace dometer::dns {
    class RCode {
        public:
            static const RCode NOERROR;
            static const RCode FORMERR;
            static const RCode SERVFAIL;
            static const RCode NXDOMAIN;
            static const RCode NOTIMPL;
            static const RCode REFUSED;

            RCode(uint8_t value);
            operator uint8_t() const;
            operator std::string() const;
        private:
            const uint8_t value;
    };
}
