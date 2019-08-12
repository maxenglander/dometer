#pragma once

#include <stdexcept>
#include <string>

namespace DnsTelemeter::Util::Error {
    class SystemException : public std::runtime_error {
        public:
            SystemException(std::string message);
            SystemException(std::string message, int errorNumber);
            std::string getErrorDescription();
            int getErrorNumber();
            std::string getMessage();
        private:
            int errorNumber;
    };
}
