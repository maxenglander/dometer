#pragma once

#include <stdint.h>
#include <string>

namespace dometer::dns {
    class dns_class {
        public:
            static const dns_class IN;
            dns_class(uint16_t value);
            operator uint16_t() const;
            operator std::string() const;
        private:
            uint16_t value;
    };
}
