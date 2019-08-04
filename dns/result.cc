#include "dns/answer.h"
#include "dns/result.h"

namespace DnsTelemeter {
    namespace Dns {
        Result::Result(std::vector<Answer> answers) {
            this->answers = answers;
        }
    }
}
