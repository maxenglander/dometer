#include <algorithm>
#include <atomic>
#include <iostream>
#include <memory>
#include <vector>

#include "asio.hpp"
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
    Server::Server(std::shared_ptr<dns::handler::Handler> handler)
        :   handler(handler),
            ioContext(std::x::make_unique<asio::io_context>()),
            sessionCounter(0),
            socket(std::x::make_unique<ip::udp::socket>(*ioContext))
    { }

    std::x::expected<void, util::Error> Server::openAndBindSocket(ip::udp::endpoint endpoint) {
        asio::error_code error;
        if(endpoint.address().is_v4()) {
            socket->open(ip::udp::v4(), error);
        } else {
            return std::x::unexpected<util::Error>(util::Error(
                "IPv6 addresses are not supported."
            ));
        }

        if(error) {
            return std::x::unexpected<util::Error>(util::Error(
                "Failed to open socket.",
                util::Error(error.message(), error.value())
            ));
        }

        socket->bind(endpoint, error);
        if(error) {
            return std::x::unexpected<util::Error>(util::Error(
                "Failed to bind socket.",
                util::Error(error.message(), error.value())
            ));
        }

        return {};
    }

    std::x::expected<void, util::Error> Server::serve(std::string bindAddress) {
        size_t separator = bindAddress.find_last_of(':');
        if(separator == std::string::npos) {
            return std::x::unexpected<util::Error>(util::Error(
                "Expected to find a ':' character in bind address.",
                std::vector<std::string>({"Bind address: " + bindAddress})
            ));
        }

        std::string host = bindAddress.substr(0, separator);
        // Sring optional [] characters from around IPv6 address
        if(host.length() > 0 && host.front() == '[')
            host.erase(0, 1);
        if(host.length() > 0 && host.back() == ']')
            host.pop_back();

        std::string portString = bindAddress.substr(separator + 1, std::string::npos);
        int port;
        try {
            port = std::stoi(portString);
        } catch(std::exception& e) {
            return std::x::unexpected<util::Error>(util::Error(
                "Could not convert port portion of bind address to integer.",
                std::vector<std::string>({
                    "Bind address: " + bindAddress,
                    "Port portion: " + portString
                }),
                util::Error(e.what())
            ));
        }

        return serve(host, port);
    }

    void Server::listen() {
        asio::error_code error;

        for(;;) {
            unsigned char queryBuffer[4096];
            size_t queryLength = 0;

            ip::udp::endpoint remoteEndpoint;
            queryLength = socket->receive_from(
                    asio::buffer(queryBuffer, sizeof(queryBuffer)), remoteEndpoint, 0, error);

            const uint64_t sessionId = ++sessionCounter;

            if(error) {
                continue;
            }

            auto reply = handler->handle(sessionId, std::vector<uint8_t>(queryBuffer, queryBuffer + queryLength));
            if(reply) {
                socket->send_to(asio::buffer(reply->data(), reply->size()), remoteEndpoint, 0, error);
            } else {
                std::cerr << "Did not receive a UDP reply" << std::endl;
            }
        }
    }

    std::x::expected<void, util::Error> Server::serve(std::string address, uint16_t port) {
        asio::error_code error;
        asio::ip::address address_ = asio::ip::make_address(address, error);
        if(error) {
            return std::x::unexpected<util::Error>(util::Error(
              "Failed to parse IP address from address.",
              std::vector<std::string>({
                  "Address: " + address,
              }),
              util::Error(error.message(), error.value())
          ));
        }

        ip::udp::endpoint endpoint(address_, port);

        return serve(endpoint);
    }

    std::x::expected<void, util::Error> Server::serve(ip::udp::endpoint endpoint) {
        std::x::expected<void, util::Error> result = openAndBindSocket(endpoint);
        if(!result) {
            return std::x::unexpected<util::Error>(util::Error(
                "Failed to open and bind socket.",
                result.error()
            ));
        }

        listen();

        return {};
    }
}
