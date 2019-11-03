#include <string>
#include <tuple>

#include "dns/metrics/reply_counter.hpp"
#include "metrics/counter.hpp"
#include "metrics/labels.hpp"

namespace dometer::dns::metrics {
    const ReplyCounter ReplyCounter::INSTANCE = ReplyCounter();

    ReplyCounter::ReplyCounter()
            :   dometer::metrics::Counter<std::string, std::string, std::string, bool>::Counter(
                    "dns_reply_sent_count", "Count of DNS replies returned by Dometer to clients",
                    std::make_tuple(
                        dometer::metrics::Labels::string("qclass"), 
                        dometer::metrics::Labels::string("qname"),
                        dometer::metrics::Labels::string("qtype"),
                        dometer::metrics::Labels::boolean("valid")
                    )
                )
    {}
}
