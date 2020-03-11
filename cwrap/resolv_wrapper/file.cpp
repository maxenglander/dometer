#include <fstream>
#include <memory>
#include <stdio.h>
#include <utility>

#include "cwrap/resolv_wrapper/file.hpp"

namespace cwrap::resolv_wrapper {
    file::file(std::string name, std::unique_ptr<std::fstream> stream)
        : _name(name),
          _stream(std::move(stream))
    {}

    file::file(file&& _file)
        : _name(_file.name()),
          _stream(std::move(_file._stream))
    {
    }

    std::string file::name() {
        return _name;
    }

    std::fstream& file::stream() {
        return *_stream;
    }

    self_destructing_file::self_destructing_file(std::string name, std::unique_ptr<std::fstream> stream)
        : file::file(name, std::move(stream))
    {}

    self_destructing_file::self_destructing_file(self_destructing_file&& _file)
        : self_destructing_file(_file.name(), std::move(_file._stream))
    {}

    self_destructing_file::~self_destructing_file() {
        if(_stream) {
            _stream->close();
            remove(_name.c_str());
        }
    }
}
