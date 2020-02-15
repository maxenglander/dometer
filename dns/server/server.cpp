#include <algorithm>
#include <memory>

#include "asio.hpp"
#include "dns/packet.hpp"
#include "dns/server/server.hpp"
#include "dns/server/handler.hpp"
#include "dns/server/libresolv_resolving_handler.hpp"
#include "x/expected.hpp"
#include "util/error.hpp"

using namespace dometer::dns;
using namespace dometer::util;
using namespace asio::ip;
using namespace std::x;

namespace dometer::dns::server {
    Server::Server() : Server(std::make_unique<LibresolvResolvingHandler>()) {}

    Server::Server(std::unique_ptr<Handler> handler)
        :   handler(std::move(handler)),
            ioContext(std::make_unique<asio::io_context>()),
            socket(std::make_unique<asio::ip::udp::socket>(*ioContext))
    { }

    expected<void, Error> Server::openAndBindSocket(asio::ip::udp::endpoint endpoint) {
        asio::error_code error;
        if(endpoint.address().is_v4()) {
            socket->open(udp::v4(), error);
        } else {
            return unexpected<Error>(Error{
                "IPv6 addresses are not supported"
            });
        }

        if(error) {
            return unexpected<Error>(Error{
                "Failed to open socket [" + error.message() + "]",
                error.value()
            });
        }

        socket->bind(endpoint, error);
        if(error) {
            return unexpected<Error>(Error{
                "Failed to bind socket [" + error.message() + "]",
                error.value()
            });
        }

        return {};
    }

    expected<void, Error> Server::serve(std::string bindAddress) {
        size_t separator = bindAddress.find_last_of(':');
        if(separator == std::string::npos) {
            return unexpected<Error>(Error{
                "Expected to find a ':' character in bind address (" + bindAddress + ")"
            });
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
            return unexpected<Error>(Error{
                  "Failed to extract or parse port number (" + portString + ")"
                + " from bindAddress (" + bindAddress + ") [" + e.what() + "]"
            });
        }

        return serve(host, port);
    }

    void Server::listen() {
        asio::error_code error;

        for(;;) {
            unsigned char queryBuffer[4096];
            size_t queryLength = 0;

            udp::endpoint remoteEndpoint;
            queryLength = socket->receive_from(
                    asio::buffer(queryBuffer, sizeof(queryBuffer)), remoteEndpoint, 0, error);

            if(error) {
                continue;
            }

            unsigned char replyBuffer[4096];

            auto replySize = handler->handle(queryBuffer, queryLength, replyBuffer, sizeof(replyBuffer));
            if(replySize) {
                socket->send_to(asio::buffer(replyBuffer, *replySize), remoteEndpoint, 0, error);
            } else {
                socket->send_to(asio::buffer(""), remoteEndpoint, 0, error);
            }
        }
    }

    expected<void, Error> Server::serve(std::string address, uint16_t port) {
        asio::error_code error;
        asio::ip::address address_ = asio::ip::make_address(address, error);
        if(error) {
            return unexpected<Error>(Error{
              error.message(),
              error.value()
          });
        }

        udp::endpoint endpoint(address_, port);

        return serve(endpoint);
    }

    expected<void, Error> Server::serve(udp::endpoint endpoint) {
        expected<void, Error> result = openAndBindSocket(endpoint);
        if(!result) {
            return unexpected<Error>(result.error());
        }

        listen();

        return {};
    }
}
