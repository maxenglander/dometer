#include <memory>
#include <vector>

#include "dometer/util/error.hpp"

namespace dometer::util {
    Error::Error(std::exception& e) : Error(e.what()) {}
    Error::Error(std::string message) : Error(message, 0) {}
    Error::Error(std::string message, std::vector<std::string> details) : Error(message, 0, details) {}
    Error::Error(std::string message, Error cause) : Error(message, 0, cause) {}
    Error::Error(std::string message, std::vector<std::string> details, Error cause) : Error(message, 0, details, cause) {}
    Error::Error(std::string message, int code) : Error(message, code, std::vector<std::string>(), nullptr) {}
    Error::Error(std::string message, int code, std::vector<std::string> details) : Error(message, code, details, nullptr) {}
    Error::Error(std::string message, int code, Error cause) : Error(message, code, std::vector<std::string>(), cause) {}
    Error::Error(std::string message, int code, std::vector<std::string> details, Error cause)
        : Error(message, code, details, std::make_shared<Error>(cause)) {}

    Error::Error(std::string message, int code, std::vector<std::string> details, std::shared_ptr<Error> cause)
        : message(message), code(code), details(details), cause(cause) {}

}
