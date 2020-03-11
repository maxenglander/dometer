#pragma once

#include <fstream>
#include <memory>

namespace cwrap::resolv_wrapper {
    class file {
        public:
            file(std::string name, std::unique_ptr<std::fstream> stream);
            file(const file&) = delete;
            file(file&&);
            std::string name();
            std::fstream& stream();
        protected:
            std::string _name;
            std::unique_ptr<std::fstream> _stream;
    };

    class self_destructing_file : public file {
        public:
            self_destructing_file(std::string name, std::unique_ptr<std::fstream> stream);
            self_destructing_file(const self_destructing_file&) = delete;
            self_destructing_file(self_destructing_file&&);
            ~self_destructing_file();
    };
}
