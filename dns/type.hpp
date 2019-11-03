#pragma once

#include <stdint.h>
#include <string>

namespace dometer::dns {
    class Type {
        public:
            static const Type A;
            Type(uint16_t value);
            operator uint16_t() const;
            operator std::string() const;
        private:
            uint16_t value;
    };
}
