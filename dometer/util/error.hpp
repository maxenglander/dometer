#pragma once

#include <memory>
#include <string>
#include <vector>

namespace dometer::util {
    struct Error {
        Error(std::exception&);
        Error(std::string);
        Error(std::string, std::vector<std::string>);
        Error(std::string, Error);
        Error(std::string, std::vector<std::string>, Error);
        Error(std::string, int);
        Error(std::string, int, std::vector<std::string>);
        Error(std::string, int, Error);
        Error(std::string, int, std::vector<std::string>, Error);

        const std::string message;
        const int code;
        const std::vector<std::string> details;
        const std::shared_ptr<Error> cause;

        private:
            Error(std::string, int, std::vector<std::string>, std::shared_ptr<Error>);
    };
}
