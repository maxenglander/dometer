#include "network/dns/answer.h"
#include "network/dns/result.h"

namespace Dometer::Network::Dns {
    Result::Result(std::vector<Answer> answers, bool succeeded) {
        this->answers = answers;
        this->_succeeded = succeeded;
    }

    Result Result::failure() {
        return Result(std::vector<Answer>(), false);
    }

    std::vector<Answer> Result::getAnswers() {
        return this->answers;
    }

    bool Result::succeeded() {
        return this->_succeeded;
    }

    Result Result::success(std::vector<Answer> answers) {
        return Result(answers, true);
    }
}
