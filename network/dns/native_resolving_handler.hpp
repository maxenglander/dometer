#pragma once

#include "experimental/expected.hpp"
#include "network/dns/handler.hpp"
#include "network/dns/native_resolver.hpp"
#include "network/dns/packet.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    class NativeResolvingHandler : public Handler {
        public:
            NativeResolvingHandler(NativeResolver);
            expected<Packet, Error> handle(Packet&) const;
        private:
            const NativeResolver resolver;
    };
}
