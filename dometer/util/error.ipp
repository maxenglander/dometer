#pragma once

#include <memory>
#include <vector>

#include "dometer/util/error.hpp"

namespace dometer::util {
    template <typename Code>
    GenericError::GenericError(std::exception& e) : GenericError<Code>(e.what()) {}

    template <typename Code>
    GenericError::GenericError(std::string message) : GenericError<Code>(message, Code()) {}

    template <typename Code>
    GenericError::GenericError(std::string message, std::vector<std::string> details)
        : GenericError<Code>(message, Code(), details) {}

    template <typename Code>
    GenericError::GenericError(std::string message, GenericError cause)
        : GenericError<Code>(message, Code(), cause) {}

    template <typename Code>
    GenericError::GenericError(std::string message, std::vector<std::string> details, GenericError cause)
        : GenericError<Code>(message, Code(), details, cause) {}

    template <typename Code>
    GenericError::GenericError(std::string message, Code code)
        : GenericError(message, code, std::vector<std::string>(), nullptr) {}

    template <typename Code>
    GenericError::GenericError(std::string message, Code code, std::vector<std::string> details)
        : GenericError(message, code, details, nullptr) {}

    template <typename Code>
    GenericError::GenericError(std::string message, Code code, GenericError cause)
        : GenericError(message, code, std::vector<std::string>(), cause) {}

    template <typename Code>
    GenericError::GenericError(std::string message, Code code, std::vector<std::string> details, GenericError cause)
        : GenericError(message, code, details, std::make_shared<GenericError>(cause)) {}

    template <typename Code>
    GenericError::GenericError(std::string message, Code codel,
            std::vector<std::string> details, std::shared_ptr<GenericError> cause)
        : std::runtime_error(message), message(message), code(code), details(details), cause(cause) {}

    const char* GenericError::what() const throw() {
        return message.c_str();
    }
}
