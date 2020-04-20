#include <memory>
#include <vector>

#include "dometer/util/error.hpp"

namespace dometer::util {
    error::error(const error& error)
        : message(error.message), code(error.code), details(error.details), cause(error.cause) {}
    error::error(std::string message) : error(message, 0) {}
    error::error(std::string message, std::vector<std::string> details) : error(message, 0, details) {}
    error::error(std::string message, error cause) : error(message, 0, cause) {}
    error::error(std::string message, std::vector<std::string> details, error cause) : error(message, 0, details, cause) {}
    error::error(std::string message, int code) : error(message, code, std::vector<std::string>(), nullptr) {}
    error::error(std::string message, int code, std::vector<std::string> details) : error(message, code, details, nullptr) {}
    error::error(std::string message, int code, error cause) : error(message, code, std::vector<std::string>(), cause) {}
    error::error(std::string message, int code, std::vector<std::string> details, error cause)
        : error(message, code, details, std::make_shared<error>(cause)) {}
    error::error(std::string message, int code, std::vector<std::string> details, std::shared_ptr<error> cause)
        : message(message), code(code), details(details), cause(cause) {}
}
