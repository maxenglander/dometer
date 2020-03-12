#pragma once

#include <functional>
#include <memory>

namespace cwrap::resolv_wrapper {
    class file {
        public:
            static file make_temporary_file();

            file(std::string name, std::unique_ptr<std::FILE, std::function<void(std::FILE*)>> pointer);
            file(const file&) = delete;
            file(file&&);
            void close();
            std::FILE& handle();
            std::string name();
        protected:
            bool _moved;
            std::string _name;
            std::unique_ptr<std::FILE, std::function<void(std::FILE*)>> _pointer;
    };
}
