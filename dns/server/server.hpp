#pragma once

#include <memory>

#include "asio.hpp"
#include "dns/server/handler.hpp"
#include "util/error.hpp"

using namespace dometer::util;
using namespace std::x;

namespace dometer::dns::server {
    class Server {
        public:
            Server(std::unique_ptr<Handler>);
            expected<void, Error> serve(std::string);
            expected<void, Error> serve(std::string, uint16_t port);
        private:
            void listen();
            expected<void, Error> openAndBindSocket(asio::ip::udp::endpoint);
            expected<void, Error> serve(asio::ip::udp::endpoint);

            const std::unique_ptr<Handler> handler;
            const std::unique_ptr<asio::io_context> ioContext;
            const std::unique_ptr<asio::ip::udp::socket> socket;
    };
}
