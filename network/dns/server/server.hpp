#pragma once

#include <chrono>
#include <memory>

#include "asio.hpp"
#include "network/dns/server/handler.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
    class Server {
        public:
            Server();
            Server(std::chrono::steady_clock, std::unique_ptr<Handler>);
            expected<void, Error> serve();
            expected<void, Error> serve(uint16_t port);
        private:
            const std::chrono::steady_clock clock;
            const std::unique_ptr<Handler> handler;
    };
}
