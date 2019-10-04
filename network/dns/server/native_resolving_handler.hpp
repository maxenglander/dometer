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
            expected<size_t, Error> handle(
                    uint8_t *queryPtr, size_t querySize,
                    uint8_t *replyPtr, size_t replySize) const;
        private:
            expected<Packet, Error> handle(const expected<Packet, Error> &query) const;
            const NativeResolver resolver;
    };
}
