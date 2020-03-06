#pragma once

#include <memory>
#include <string>
#include <vector>

namespace dometer::util {
    struct error {
        error(const error&);
        error(std::string);
        error(std::string, std::vector<std::string>);
        error(std::string, error);
        error(std::string, std::vector<std::string>, error);
        error(std::string, int);
        error(std::string, int, std::vector<std::string>);
        error(std::string, int, error);
        error(std::string, int, std::vector<std::string>, error);

        const std::string message;
        const int code;
        const std::vector<std::string> details;
        const std::shared_ptr<error> cause;

        private:
            error(std::string, int, std::vector<std::string>, std::shared_ptr<error>);
    };
}
