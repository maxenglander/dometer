#include <vector>

#include "dometer/dns/record/class.hpp"
#include "dometer/dns/record/record.hpp"
#include "dometer/dns/record/type.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/util/error.hpp"
#include "gmock/gmock.h"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;

namespace dometer::dns::resolver {
    class mock_resolver : public resolver {
        public:
            MOCK_METHOD((std::x::expected<std::vector<uint8_t>, error>),
                        resolve,
                        (const std::string&, const dns::record::class_&, const dns::record::type&),
                        (const, override));
    };
}
