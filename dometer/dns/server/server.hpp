#pragma once

#include <atomic>
#include <memory>
#include <thread>

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
            server(std::shared_ptr<dns::handler::handler>);
            server(dometer::event::emitter<dometer::dns::event::any_event>, std::shared_ptr<dns::handler::handler>);
            void join();
            std::x::expected<void, util::error> start(std::string);
            std::x::expected<void, util::error> start(std::string, uint16_t port);
        private:
            void accept_requests();
            std::x::expected<void, util::error> open_and_bind_socket(asio::ip::udp::endpoint);
            std::x::expected<void, util::error> start(asio::ip::udp::endpoint);

            std::thread acceptor_thread;
            dometer::event::emitter<dometer::dns::event::any_event> emitter;
            const std::shared_ptr<dns::handler::handler> handler;
            const std::unique_ptr<asio::io_context> io_context;
            std::atomic<uint64_t> session_counter;
            const std::unique_ptr<asio::ip::udp::socket> socket;
            asio::thread_pool worker_pool;
    };
}
