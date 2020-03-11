#pragma once

#include "cwrap/resolv_wrapper/file.hpp"
#include "cwrap/resolv_wrapper/wrap_mode.hpp"

namespace cwrap::resolv_wrapper {
    class resolv_wrapper {
        public:
            resolv_wrapper(file, wrap_mode);
            resolv_wrapper(const resolv_wrapper&) = delete;
            resolv_wrapper(resolv_wrapper&&);
            ~resolv_wrapper();
            void disable();
            void enable();
        private:
            file _file;
            wrap_mode _mode;
    };
}
