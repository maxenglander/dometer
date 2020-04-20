#include <vector>

#include "dometer/dns/class.hpp"
#include "dometer/dns/record.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/message_factory.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/resolver/mock_resolver.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;

namespace dometer::dns::resolver {
    mock_resolver::mock_resolver(const mock_resolver& resolver)
        : _records(resolver._records)
    {}

    mock_resolver::add_record(dns::record record) {
        _records.push_back(record);
    }

    std::x::expected<std::vector<uint8_t>, error> resolve(
        const std::string& qname, const dns::class_& qclass, const dns::type& qtype
    ) const {
        for(auto it = _records.begin(); it < _records.end(); it++) {
            auto record = *it;
            if(it.name == qname && it.type == qtype) {
            }
        }

        return message_factory::nxdomain();
    }
}
