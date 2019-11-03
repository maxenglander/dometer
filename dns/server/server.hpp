#pragma once

#include <memory>

#include "asio.hpp"
#include "dns/server/handler.hpp"
#include "util/error.hpp"

using namespace dometer::util;
using namespace std::experimental;

namespace dometer::dns::server {
    class Server {
        public:
            Server();
            Server(std::unique_ptr<Handler>);
            expected<void, Error> serve();
            expected<void, Error> serve(uint16_t port);
        private:
            const std::unique_ptr<Handler> handler;
    };
}
