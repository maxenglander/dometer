#include <cstdio>
#include <functional>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stdexcept>
#include <utility>

#include "cwrap/resolv_wrapper/file.hpp"

namespace cwrap::resolv_wrapper {
    file file::make_temporary_file() {
        char _buffer[L_tmpnam + 1];
        if(std::tmpnam(_buffer) == NULL) {
            throw new std::runtime_error("Failed to create temporary file name.");
        }

        std::string _file_name(_buffer);
        std::FILE* _fp = fopen(_file_name.c_str(), "w+");
        if(_fp == NULL) {
            throw new std::runtime_error("Failed to open temporary file.");
        }

        std::unique_ptr<std::FILE, std::function<void(std::FILE*)>> _file_pointer(_fp, [_file_name](std::FILE* fp) {
            std::fclose(fp);
            remove(_file_name.c_str());
        });

        return file(_file_name, std::move(_file_pointer));
    }

    file::file(std::string name, std::unique_ptr<std::FILE, std::function<void(std::FILE*)>> pointer)
        : _name(name),
          _pointer(std::move(pointer))
    {}

    file::file(file&& _file)
        : _name(_file.name()),
          _pointer(std::move(_file._pointer))
    {
        _moved = true;
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
}
