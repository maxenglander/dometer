#pragma once

#include <vector>

#include "dns/answer.h"

namespace DnsTelemeter::Dns {
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
