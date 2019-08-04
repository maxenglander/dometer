#include "dns/answer.h"
#include "dns/result.h"
#include "dns/query.h"

namespace DnsTelemeter {
    namespace Dns {
        Result lookup(Query query) {
            return Result(std::vector<Answer>());
        }
    }
}
