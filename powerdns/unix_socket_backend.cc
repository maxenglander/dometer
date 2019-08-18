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

        if(!(*serverSocket).bind(socketPath)) {
            return unexpected<std::string>(std::string("Failed to bind server socket to: " + socketPath));
        }

        if(!(*serverSocket).listen(this->maxConnections)) {
            return unexpected<std::string>(std::string("Failed to listen for connections"));
        }

        Json::Value  jsonIn;
        Json::Value  jsonOut;
        Json::CharReaderBuilder readerBuilder;
        Json::CharReader * reader = readerBuilder.newCharReader();
        Json::StreamWriterBuilder writerBuilder;
        Json::StreamWriter * writer = writerBuilder.newStreamWriter();

        for(;;) {
            auto clientSocket = (*serverSocket).accept();
            if(!clientSocket) continue;
            while(auto message = (*clientSocket).readLine(maxMessageSize)) {
                jsonOut["result"] = Json::Value(false);
                if(reader->parse((*message).data(), (*message).data() + (*message).size(), &jsonIn, NULL)) {

                }
                std::stringbuf buffer;
                std::ostream   stream(&buffer);
                writer->write(jsonOut, &stream);
                (*clientSocket).write(buffer.str());
            }
        }
    }
}
