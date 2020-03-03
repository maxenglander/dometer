#pragma once

#include <atomic>
#include <memory>

#include "asio.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/util/error.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::server {
    class Server {
        public:
            Server(std::shared_ptr<dns::handler::Handler>);
            std::x::expected<void, util::Error> serve(std::string);
            std::x::expected<void, util::Error> serve(std::string, uint16_t port);
        private:
            void listen();
            std::x::expected<void, util::Error> openAndBindSocket(asio::ip::udp::endpoint);
            std::x::expected<void, util::Error> serve(asio::ip::udp::endpoint);

            const std::shared_ptr<dns::handler::Handler> handler;
            const std::unique_ptr<asio::io_context> ioContext;
            std::atomic<uint64_t> sessionCounter;
            const std::unique_ptr<asio::ip::udp::socket> socket;
    };
}
