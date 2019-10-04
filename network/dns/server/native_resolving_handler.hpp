#pragma once

#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/resolver/native_resolver.hpp"
#include "network/dns/server/handler.hpp"
#include "util/error.hpp"

using namespace Dometer::Network::Dns;
using namespace Dometer::Network::Dns::Resolver;
using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
    class NativeResolvingHandler : public Handler {
        public:
            NativeResolvingHandler();
            NativeResolvingHandler(NativeResolver);
            expected<Packet, Error> handle(Packet&) const;
        private:
            const NativeResolver resolver;
    };
}
