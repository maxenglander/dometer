#include <cstdio>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stdexcept>
#include <utility>

#include "cwrap/resolv_wrapper/file.hpp"

namespace cwrap::resolv_wrapper {
    const uint8_t file::flags::none = 0 << 0;
    const uint8_t file::flags::self_destruct = 1 << 0;

    file file::make_temporary_file(const std::string mode) {
        char _buffer[L_tmpnam + 1];
        if(std::tmpnam(_buffer) == NULL) {
            throw new std::runtime_error("Failed to create temporary file name.");
        }

        std::string _file_name(_buffer);
        std::unique_ptr<std::FILE, std::function<void(std::FILE*)>> _file_pointer(
            std::fopen(_file_name.c_str(), mode.c_str()),
            [](std::FILE* fp) {}
        );

        if(!_file_pointer) {
            throw new std::runtime_error("Failed to open temporary file.");
        }

        return file(_file_name, std::move(_file_pointer), file::flags::self_destruct);
    }

    file::file(std::string name, std::unique_ptr<std::FILE, std::function<void(FILE*)>> pointer, const uint8_t flags)
        : _name(name),
          _pointer(std::move(pointer)),
          _flags(flags)
    {}

    file::file(file&& _file)
        : _name(_file.name()),
          _pointer(std::move(_file._pointer)),
          _flags(_file._flags)
    {
    }

    file::~file() {
        if(_pointer && static_cast<bool>(_flags & file::flags::self_destruct)) {
            remove();
        }
    }

    void file::close() {
        std::fclose(&handle());
    }

    std::string file::name() {
        return _name;
    }

    std::FILE& file::handle() {
        return *_pointer;
    }

    void file::remove() {
        std::remove(_name.c_str());
    }
}
