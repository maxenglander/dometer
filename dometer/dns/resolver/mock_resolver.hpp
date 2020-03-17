#include <vector>

#include "dometer/dns/class.hpp"
#include "dometer/dns/record.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/util/error.hpp"
#include "gmock/gmock.h"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;

namespace dometer::dns::resolver {
    class mock_resolver : public resolver {
        public:
            mock_resolver() {}
            mock_resolver(mock_resolver&&) {}
            MOCK_METHOD((std::x::expected<std::vector<uint8_t>, error>),
                        resolve,
                        (const std::string&, const dns::class_&, const dns::type&),
                        (const, override));
    };
}
