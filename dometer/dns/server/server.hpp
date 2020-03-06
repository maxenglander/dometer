#pragma once

#include <atomic>
#include <memory>

#include "asio.hpp"
#include "dometer/event/emitter.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/util/error.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::server {
    class server {
        public:
            server(dometer::event::emitter<dometer::dns::event::any_event>, std::shared_ptr<dns::handler::Handler>);
            std::x::expected<void, util::error> serve(std::string);
            std::x::expected<void, util::error> serve(std::string, uint16_t port);
        private:
            void listen();
            std::x::expected<void, util::error> openAndBindSocket(asio::ip::udp::endpoint);
            std::x::expected<void, util::error> serve(asio::ip::udp::endpoint);

            dometer::event::emitter<dometer::dns::event::any_event> emitter;
            const std::shared_ptr<dns::handler::Handler> handler;
            const std::unique_ptr<asio::io_context> ioContext;
            uint64_t sessionCounter;
            //std::atomic<uint64_t> sessionCounter;
            const std::unique_ptr<asio::ip::udp::socket> socket;
    };
}
