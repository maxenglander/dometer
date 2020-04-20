#pragma once

#include <string>

#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns::server {
    class server {
        public:
            virtual void join() = 0;
            virtual std::x::expected<void, dometer::util::error> start(std::string) = 0;
            virtual void stop() = 0;
    };
}
