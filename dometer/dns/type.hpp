#pragma once

#include <stdint.h>
#include <string>

namespace dometer::dns {
    class type {
        public:
            static const type A;

            type(uint16_t value);
            operator uint16_t() const;
            operator std::string() const;
        private:
            uint16_t value;
    };
}
