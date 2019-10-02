#include <arpa/nameser.h>
#include <iostream>

#include "asio.hpp"
#include "experimental/expected.hpp"
#include "network/dns/native_resolver.hpp"
#include "network/dns/opcode.hpp"
#include "network/dns/packet.hpp"

using namespace Dometer::Network;
using namespace asio::ip;
using namespace std::experimental;

int main(int argc, char **argv) {
    asio::io_context ioContext;
    udp::socket socket(ioContext, udp::endpoint(udp::v4(), 53));

    Dns::NativeResolver resolver;

    for(;;) {
        unsigned char buffer[PACKETSZ];
        size_t length;

        udp::endpoint senderEndpoint;
        length = socket.receive_from(
            asio::buffer(buffer, sizeof(buffer)), senderEndpoint);

        expected<Dns::Packet, Error> query = Dns::Packet::makePacket(buffer, length);

        if(!query) {
            // Send empty response
            fprintf(stderr, "failed to parse query: %s (%d)\n", query.error().message.c_str(), query.error().number);
            socket.send_to(asio::buffer(""), senderEndpoint);
        } else if(query->opcode() != Dns::Opcode::QUERY) {
            fprintf(stderr, "opcode not implemented: %d\n", static_cast<int>(query->opcode()));
            auto reply = Dns::Packet::notImplemented(*query);
            socket.send_to(asio::buffer(*reply, reply->size), senderEndpoint);
        } else if(query->qdcount() != 1) {
            // TODO: signal FORMERR
            fprintf(stderr, "qdcount is invalid: %d\n", query->qdcount());
            auto reply = Dns::Packet::formatError(*query);
            socket.send_to(asio::buffer(*reply, reply->size), senderEndpoint);
        } else {
            auto question = query->question();

            if(!question) {
                // TODO: signal FORMERR
                fprintf(stderr, "failed to parse question: %s (%d)\n",
                        question.error().message.c_str(), question.error().number);
                continue;
            }

            fprintf(stdout, "msg id: %d; dname: %s; class: %s; type %s; opcode: %d\n",
                    query->id(), question->qname.c_str(), ((std::string)question->qclass).c_str(),
                    ((std::string)question->qtype).c_str(), static_cast<uint16_t>(query->opcode())); 

            auto reply = resolver.resolve(*query);

            if(!reply) {
                // TODO: signal SERVFAIL
                fprintf(stderr, "failed to get reply: %s (%d)\n", reply.error().message.c_str(), reply.error().number); 
                continue;
            } else {
                socket.send_to(asio::buffer(*reply, reply->size), senderEndpoint);
            }
        }
    }

    return 0;
}
