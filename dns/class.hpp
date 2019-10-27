#pragma once

#include <stdint.h>
#include <string>

namespace Dometer::Dns {
    class Class {
        public:
            Class(uint16_t value);
            operator uint16_t() const;
            operator std::string() const;
        private:
            uint16_t value;
    };
}
