#include <memory>

#include "asio.hpp"
#include "dns/packet.hpp"
#include "dns/server/server.hpp"
#include "dns/server/handler.hpp"
#include "dns/server/native_resolving_handler.hpp"
#include "x/expected.hpp"
#include "util/error.hpp"

using namespace dometer::dns;
using namespace dometer::util;
using namespace asio::ip;
using namespace std::x;

namespace dometer::dns::server {
    Server::Server() : Server(std::make_unique<NativeResolvingHandler>()) {}

    Server::Server(std::unique_ptr<Handler> handler)
        :   handler(std::move(handler))
    {}

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
            unsigned char queryBuffer[4096];
            size_t queryLength = 0;

            udp::endpoint remoteEndpoint;
            queryLength = socket.receive_from(
                    asio::buffer(queryBuffer, sizeof(queryBuffer)), remoteEndpoint, 0, errorCode);

            if(errorCode) {
                continue;
            }

            unsigned char replyBuffer[4096];

            auto replySize = handler->handle(queryBuffer, queryLength, replyBuffer, sizeof(replyBuffer));
            if(replySize) {
                socket.send_to(asio::buffer(replyBuffer, *replySize), remoteEndpoint, 0, errorCode);
            } else {
                socket.send_to(asio::buffer(""), remoteEndpoint, 0, errorCode);
            }
        }
    }
}
