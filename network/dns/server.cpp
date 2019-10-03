#include <memory>

#include "asio.hpp"
#include "experimental/expected.hpp"
#include "network/dns/handler.hpp"
#include "network/dns/native_resolving_handler.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/server.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace asio::ip;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    Server::Server() : Server(std::make_unique<NativeResolvingHandler>()) {}

    Server::Server(std::unique_ptr<Handler> handler) : handler(std::move(handler)) {}

    expected<void, Error> Server::serve() {
        return this->serve(53);
    }

    expected<void, Error> Server::serve(uint16_t port) {
        asio::error_code errorCode;
        asio::io_context ioContext;
        udp::endpoint localEndpoint(udp::v4(), port);
        udp::socket socket(ioContext);

        socket.open(udp::v4(), errorCode);
        if(!errorCode)
            socket.bind(localEndpoint, errorCode);

        if(errorCode) {
            return unexpected<Error>(Error{
                errorCode.message(),
                errorCode.value()
            });
        }

        for(;;) {
            unsigned char buffer[4096];
            size_t length;

            udp::endpoint remoteEndpoint;
            length = socket.receive_from(
                    asio::buffer(buffer, sizeof(buffer)), remoteEndpoint, 0, errorCode);

            if(errorCode) {
                continue;
            }

            expected<Packet, Error> query = Packet::makePacket(buffer, length);

            if(!query) {
                socket.send_to(asio::buffer(""), remoteEndpoint);
            } else {
                expected<Packet, Error> reply = handler->handle(*query);
                if(!reply) {
                    auto failure = Packet::serverFailure(*query);
                    socket.send_to(asio::buffer(failure, failure.size), remoteEndpoint, 0, errorCode);
                } else {
                    socket.send_to(asio::buffer(*reply, reply->size), remoteEndpoint, 0, errorCode);
                }
            }
        }
    }
}
