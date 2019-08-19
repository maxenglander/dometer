#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "json/json.h"
#include "network/socket/socket_factory.h"
#include "network/socket/unix_socket.h"
#include "powerdns/unix_socket_remote_backend.h"
#include "std/experimental/expected.h"
#include "util/json_serde.h"

#define MAX_LINE 4096

using namespace DnsTelemeter::Network::Socket;
using namespace DnsTelemeter::Util;
using namespace std::experimental;

namespace DnsTelemeter::PowerDns {
    UnixSocketRemoteBackend::UnixSocketRemoteBackend(
            JsonSerde jsonSerde,
            unsigned int maxConnections,
            unsigned int maxMessageSize,
            std::string socketPath) {
        this->jsonSerde = jsonSerde;
        this->maxConnections = maxConnections;
        this->maxMessageSize = maxMessageSize;
        this->socketPath = socketPath;
    }

    expected<void, std::string> UnixSocketRemoteBackend::serve() {
        auto serverSocket
            = DnsTelemeter::Network::Socket::SocketFactory::makeUnixSocket();

        if(!serverSocket)
            return unexpected<std::string>(std::string("Failed to create server socket"));
        if(!(*serverSocket).bind(socketPath))
            return unexpected<std::string>(std::string("Failed to bind server socket to: " + socketPath));
        if(!(*serverSocket).listen(this->maxConnections))
            return unexpected<std::string>(std::string("Failed to listen for connections"));

        for(;;) {
            auto clientSocket = (*serverSocket).accept();
            if(!clientSocket) continue;
            while(auto request = (*clientSocket).readLine(maxMessageSize)) {
                Json::Value reply;
                reply["result"] = Json::Value(false);

                std::cout << "Got request: " + *request;
                expected<Json::Value, std::string> query = jsonSerde.deserialize(*request);
                if(!query) {
                }

                (*clientSocket).write(jsonSerde.serialize(reply));
            }
            std::cerr << "No more lines to be read from client socket\n";
        }
    }
}
