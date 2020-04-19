#pragma once

#include <stdint.h>
#include <string>

namespace dometer::dns::record {
    class type {
        public:
            static const type a;

            type(uint16_t value);
            operator uint16_t() const;
            operator std::string() const;
        private:
            uint16_t value;
    };
}
