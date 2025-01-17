#pragma once

#include <atomic>
#include <memory>
#include <thread>

#include "asio.hpp"
#include "dometer/event/emitter.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/util/error.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::server {
    class basic_server : public server {
        public:
            basic_server(std::shared_ptr<dometer::event::emitter<dometer::dns::event::any_event>>,
                   std::shared_ptr<dns::handler::handler>);
            void join();
            virtual std::x::expected<void, util::error> start(std::string);
            virtual void stop();
        private:
            void handle_request();
            std::x::expected<void, util::error> open_and_bind_socket(asio::ip::udp::endpoint);
            std::x::expected<void, util::error> start(asio::ip::udp::endpoint);
            std::x::expected<void, util::error> start(std::string, uint16_t port);

            std::thread background_thread;
            char request_buffer[4096];
            const std::shared_ptr<dometer::event::emitter<dometer::dns::event::any_event>> emitter;
            const std::shared_ptr<dns::handler::handler> handler;
            const std::unique_ptr<asio::io_context> io_context;
            asio::ip::udp::endpoint remote_endpoint;
            std::atomic<uint64_t> session_counter;
            const std::unique_ptr<asio::ip::udp::socket> socket;
            asio::thread_pool worker_pool;
    };
}
