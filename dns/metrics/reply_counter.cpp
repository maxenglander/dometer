#include <string>
#include <tuple>

#include "dns/metrics/reply_counter.hpp"
#include "metrics/counter.hpp"
#include "metrics/labels.hpp"

namespace Dometer::Dns::Metrics {
    const ReplyCounter ReplyCounter::INSTANCE = ReplyCounter();

    ReplyCounter::ReplyCounter()
            :   Dometer::Metrics::Counter<std::string, std::string, std::string, bool>::Counter(
                    "dns_reply_sent_count", "Count of DNS replies returned by Dometer to clients",
                    std::make_tuple(
                        Dometer::Metrics::Labels::string("qclass"), 
                        Dometer::Metrics::Labels::string("qname"),
                        Dometer::Metrics::Labels::string("qtype"),
                        Dometer::Metrics::Labels::boolean("valid")
                    )
                )
    {}
}
