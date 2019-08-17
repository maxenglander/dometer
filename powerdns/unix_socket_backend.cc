#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "network/socket/socket_factory.h"
#include "network/socket/unix_socket.h"
#include "powerdns/unix_socket_backend.h"
#include "std/experimental/expected.h"
#include "util/read_until.h"

#define MAX_LINE 4096

using namespace DnsTelemeter::Network::Socket;
using namespace DnsTelemeter::Util;
using namespace std::experimental;

namespace DnsTelemeter::PowerDns {
    UnixSocketBackend::UnixSocketBackend(
            unsigned int maxConnections,
            unsigned int maxMessageSize,
            std::string socketPath) {
        this->socketPath = socketPath;
        this->maxConnections = maxConnections;
        this->maxMessageSize = maxMessageSize;
    }

    expected<void, std::string> UnixSocketBackend::serve() {
        auto serverSocket
            = DnsTelemeter::Network::Socket::SocketFactory::makeUnixSocket();

        if(!serverSocket) {
            return unexpected<std::string>(std::string("Failed to create server socket"));
        }

        (*serverSocket).bind(this->socketPath);
        (*serverSocket).listen(this->maxConnections);

        for(;;) {
            auto clientSocket = (*serverSocket).accept();
            if(!clientSocket) continue;
            while(auto message = (*serverSocket).readLine(this->maxMessageSize)) {
                std::cout << "Got a message from the client";
            }
        }
    }
}
