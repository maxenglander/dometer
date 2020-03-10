#pragma once

#include <memory>
#include <mutex>

#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns::util {
    class resolv_wrapper {
        public:
            ~resolv_wrapper();
            static std::unique_ptr<resolv_wrapper> make_resolv_wrapper();
        private:
            resolv_wrapper(std::mutex&);
            std::lock_guard<std::mutex> _lock;
            static std::mutex _mutex;
    };
}
