#include <fstream>
#include <memory>
#include <stdlib.h>
#include <utility>
#include <stdexcept>

#include "cwrap/resolv_wrapper/file.hpp"
#include "cwrap/resolv_wrapper/resolv_wrapper.hpp"
#include "cwrap/resolv_wrapper/wrap_mode.hpp"

namespace cwrap::resolv_wrapper {
    resolv_wrapper::resolv_wrapper(file _file, wrap_mode mode)
        : _file(std::move(_file)),
          _mode(mode)
    {
        enable();
    }

    resolv_wrapper::resolv_wrapper(resolv_wrapper&& wrapper)
        : resolv_wrapper(std::move(wrapper._file), wrapper._mode)
    {}

    resolv_wrapper::~resolv_wrapper() {
        disable();
    }

    void resolv_wrapper::disable() {
        switch(_mode) {
            case wrap_mode::conf:
                unsetenv("RESOLV_WRAPPER_CONF");
                break;
            case wrap_mode::hosts:
                unsetenv("RESOLV_WRAPPER_HOSTS");
                break;
        }
    }

    void resolv_wrapper::enable() {
        switch(_mode) {
            case wrap_mode::conf:
                if(0 != setenv("RESOLV_WRAPPER_CONF", _file.name().c_str(), true))
                    throw new std::runtime_error("Failed to set RESOLV_WRAPPER_CONF environment variable.");
                break;
            case wrap_mode::hosts:
                if(0 != setenv("RESOLV_WRAPPER_HOSTS", _file.name().c_str(), true))
                    throw new std::runtime_error("Failed to set RESOLV_WRAPPER_HOSTS environment variable.");
                break;
        }
    }

    std::string resolv_wrapper::file_name() {
        return _file.name();
    }

    wrap_mode resolv_wrapper::mode() {
        return _mode;
    }
}
