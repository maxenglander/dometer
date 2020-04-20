#pragma once

#include <stdint.h>
#include <string>

namespace dometer::dns::message {
    class rcode {
        public:
            static const rcode noerror;
            static const rcode formerr;
            static const rcode servfail;
            static const rcode nxdomain;
            static const rcode notimpl;
            static const rcode refused;

            rcode(uint8_t value);
            operator uint8_t() const;
            operator std::string() const;
        private:
            const uint8_t value;
    };
}
