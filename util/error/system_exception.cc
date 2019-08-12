#include <stdexcept>
#include <string.h>

#include "util/error/system_exception.h"

namespace DnsTelemeter::Util::Error {
    SystemException::SystemException(std::string message) : SystemException(message, errno) {}

    SystemException::SystemException(std::string message, int errorNumber) : std::runtime_error(message) {
        this->errorNumber = 0;
    }

    int SystemException::getErrorNumber() {
        return this->errorNumber;
    }

    std::string SystemException::getErrorDescription() {
        return std::string(strerror(this->getErrorNumber()));
    }

    std::string SystemException::getMessage() {
        return std::runtime_error::what();
    }
}
