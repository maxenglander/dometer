#pragma once

#include <vector>

#include "dns/answer.h"

namespace DnsTelemeter {
    namespace Dns {
        class Result {
            public:
                Result(std::vector<Answer> answers);
            private:
                std::vector<Answer> answers;
        };
    }
}
