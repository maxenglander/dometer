#include <algorithm>
#include <atomic>
#include <iostream>
#include <memory>
#include <vector>

#include "asio.hpp"
#include "dometer/event/emitter.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/event/start_session_event.hpp"
#include "dometer/dns/event/stop_session_event.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"
#include "std/x/unique.hpp"

namespace dns = dometer::dns;
namespace ip = asio::ip;
namespace util = dometer::util;

namespace dometer::dns::server {
    server::server(std::shared_ptr<dns::handler::handler> handler)
        : server(std::shared_ptr<dometer::event::emitter<dometer::dns::event::any_event>>(), handler)
    {}

    server::server(
            std::shared_ptr<dometer::event::emitter<dometer::dns::event::any_event>> emitter, 
            std::shared_ptr<dns::handler::handler> handler
    )   :   emitter(emitter),
            handler(handler),
            io_context(std::x::make_unique<asio::io_context>()),
            session_counter(0),
            socket(std::x::make_unique<ip::udp::socket>(*io_context)),
            worker_pool(4)
    { }

    void server::handle_request() {
        socket->async_receive_from(
            asio::buffer(request_buffer, sizeof(request_buffer)), remote_endpoint,
            [this](asio::error_code ec, size_t bytes_received) {
                if(!ec && bytes_received > 0) {
                    const uint64_t session_id = session_counter++;
                    emitter->emit(dometer::dns::event::start_session_event(session_id));

                    auto reply = handler->handle(session_id,
                                                 std::vector<uint8_t>(request_buffer, request_buffer + bytes_received));
                    if(reply) {
                        socket->send_to(asio::buffer(reply->data(), reply->size()), remote_endpoint, 0, ec);
                    }

                    emitter->emit(dometer::dns::event::stop_session_event(session_id));
                }

                handle_request();
            }
        );
    }

    void server::join() {
        background_thread.join();
    }

    std::x::expected<void, util::error> server::open_and_bind_socket(ip::udp::endpoint endpoint) {
        asio::error_code error;
        if(endpoint.address().is_v4()) {
            socket->open(ip::udp::v4(), error);
        } else {
            return std::x::unexpected<util::error>(util::error(
                "IPv6 addresses are not supported."
            ));
        }

        if(error) {
            return std::x::unexpected<util::error>(util::error(
                "Failed to open socket.",
                util::error(error.message(), error.value())
            ));
        }

        socket->bind(endpoint, error);
        if(error) {
            return std::x::unexpected<util::error>(util::error(
                "Failed to bind socket.",
                util::error(error.message(), error.value())
            ));
        }

        return {};
    }

    std::x::expected<void, util::error> server::start(std::string bind_address) {
        size_t separator = bind_address.find_last_of(':');
        if(separator == std::string::npos) {
            return std::x::unexpected<util::error>(util::error(
                "Expected to find a ':' character in bind address.",
                std::vector<std::string>({"Bind address: " + bind_address})
            ));
        }

        std::string host = bind_address.substr(0, separator);
        // Sring optional [] characters from around IPv6 address
        if(host.length() > 0 && host.front() == '[')
            host.erase(0, 1);
        if(host.length() > 0 && host.back() == ']')
            host.pop_back();

        std::string port_string = bind_address.substr(separator + 1, std::string::npos);
        int port;
        try {
            port = std::stoi(port_string);
        } catch(std::exception& e) {
            return std::x::unexpected<util::error>(util::error(
                "Could not convert port portion of bind address to integer.",
                std::vector<std::string>({
                    "Bind address: " + bind_address,
                    "Port portion: " + port_string
                }),
                util::error(e.what())
            ));
        }

        return start(host, port);
    }

    std::x::expected<void, util::error> server::start(std::string address, uint16_t port) {
        asio::error_code error;
        asio::ip::address address_ = asio::ip::make_address(address, error);
        if(error) {
            return std::x::unexpected<util::error>(util::error(
              "Failed to parse IP address from address.",
              std::vector<std::string>({
                  "Address: " + address,
              }),
              util::error(error.message(), error.value())
          ));
        }

        ip::udp::endpoint endpoint(address_, port);

        return start(endpoint);
    }

    std::x::expected<void, util::error> server::start(ip::udp::endpoint endpoint) {
        std::x::expected<void, util::error> result = open_and_bind_socket(endpoint);
        if(!result) {
            return std::x::unexpected<util::error>(util::error(
                "Failed to open and bind socket.",
                result.error()
            ));
        }

        background_thread = std::thread([&]{
            handle_request();
            io_context->run();
        });

        return {};
    }

    void server::stop() {
        io_context->stop();
        join();
    }
}
