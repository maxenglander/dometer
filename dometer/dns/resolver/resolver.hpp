#pragma once

#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;
using namespace std::x;

namespace dometer::dns::resolver {
    class Resolver {
        public:
            virtual expected<dns::message::Message, util::Error> resolve(const std::string&, const Class&, const Type&) const = 0;
    };
}
