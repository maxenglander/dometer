#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <iostream>
#include <netdb.h>
#include <resolv.h>

#include "asio.hpp"
#include "experimental/expected.hpp"
#include "network/dns/native_resolver.hpp"
#include "network/dns/packet.hpp"

using namespace Dometer::Network;
using namespace std::experimental;
using namespace asio::ip;

int main(int argc, char **argv) {
    asio::io_context io_context;
    udp::socket socket(io_context, udp::endpoint(udp::v4(), 53));

    Dns::NativeResolver resolver;

    for(;;) {
        unsigned char in_buf[PACKETSZ];
        size_t in_len;

        udp::endpoint sender_endpoint;
        in_len = socket.receive_from(
            asio::buffer(in_buf, sizeof(in_buf)), sender_endpoint);

        expected<Dns::Packet, Error> query = Dns::Packet::makePacket(in_buf, in_len);

        if(!query) {
            // TODO
            fprintf(stderr, "failed to parse query query: %s (%d)\n", query.error().message.c_str(), query.error().number);
        }

        fprintf(stdout, "byte[0] = %d, byte[1] = %d, id = %d\n", in_buf[0], in_buf[1], query->header.id);

        if(query->header.qdcount != 1) {
            // TODO
            fprintf(stderr, "qd count is incorrect: %d\n", query->header.qdcount);
        }

        auto question = query->question();

        if(!question) {
            fprintf(stderr, "failed to parse question: %s (%d)\n", question.error().message.c_str(), question.error().number);
        }

        fprintf(stdout, "msg id: %d; dname: %s; class: %s; type %s\n", query->header.id, question->qname.c_str(), ((std::string)question->qclass).c_str(), ((std::string)question->qtype).c_str()); 

        auto response = resolver.resolve(*query);

        if(!response) {
            // TODO
            fprintf(stderr, "failed to get response: %s (%d)\n", response.error().message.c_str(), response.error().number); 
        } else {
            socket.send_to(asio::buffer(*response, response->size), sender_endpoint);
        }
    }

    return 0;
}
