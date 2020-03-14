#pragma once

#include <cstdio>
#include <functional>
#include <memory>
#include <string>

namespace cwrap::resolv_wrapper {
    class file {
        struct flags {
            static const uint8_t none;
            static const uint8_t self_destruct;
        };

        public:
            static file make_temporary_file(const std::string);

            file(std::string name, std::unique_ptr<std::FILE, std::function<void(std::FILE*)>> pointer, const uint8_t);
            file(const file&) = delete;
            file(file&&);
            ~file();
            void close();
            std::FILE& handle();
            std::string name();
            void remove();
        protected:
            std::string _name;
            std::unique_ptr<std::FILE, std::function<void(FILE*)>> _pointer;
            uint8_t _flags;
    };
}
