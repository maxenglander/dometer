#include <arpa/nameser.h>
#include <iostream>

#include "asio.hpp"
#include "experimental/expected.hpp"
#include "network/dns/native_resolver.hpp"
#include "network/dns/opcode.hpp"
#include "network/dns/packet.hpp"

using namespace Dometer::Network;
using namespace std::experimental;
using namespace asio::ip;

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
            // TODO: signal FORMERR
            fprintf(stderr, "failed to parse query query: %s (%d)\n", query.error().message.c_str(), query.error().number);
            continue;
        }

        if(query->opcode() != Dns::Opcode::QUERY) {
            // TODO: signal NOTIMP or REFUSE
            fprintf(stderr, "opcode not implemented: %d\n", static_cast<int>(query->opcode()));
            continue;
        }

        if(query->qdcount() != 1) {
            // TODO: signal FORMERR
            fprintf(stderr, "qdcount is invalid: %d\n", query->qdcount());
            continue;
        }

        auto question = query->question();

        if(!question) {
            // TODO: signal FORMERR
            fprintf(stderr, "failed to parse question: %s (%d)\n",
                    question.error().message.c_str(), question.error().number);
            continue;
        }

        fprintf(stdout, "msg id: %d; dname: %s; class: %s; type %s\n",
                query->id(), question->qname.c_str(), ((std::string)question->qclass).c_str(),
                ((std::string)question->qtype).c_str()); 

        auto response = resolver.resolve(*query);

        if(!response) {
            // TODO: signal SERVFAIL
            fprintf(stderr, "failed to get response: %s (%d)\n", response.error().message.c_str(), response.error().number); 
            continue;
        } else {
            socket.send_to(asio::buffer(*response, response->size), senderEndpoint);
        }
    }

    return 0;
}
