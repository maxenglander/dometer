#pragma once

#include <vector>

#include "network/dns/answer.h"

namespace Dometer::Network::Dns {
    class Result {
        public:
            static Result failure();
            std::vector<Answer> getAnswers();
            bool succeeded();
            static Result success(std::vector<Answer> answers);
        private:
            Result(std::vector<Answer> answers, bool succeeded);
            std::vector<Answer> answers;
            bool _succeeded;
    };
}
