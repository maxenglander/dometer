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
        ns_class in_class;
        ns_msg in_h;
        u_int16_t in_id;
        ns_rr in_qr;
        const char *in_name;
        size_t in_len;
        ns_type in_type;

        unsigned char out_buf[PACKETSZ];
        ns_msg out_h;
        size_t out_len;

        udp::endpoint sender_endpoint;
        in_len = socket.receive_from(
            asio::buffer(in_buf, sizeof(in_buf)), sender_endpoint);

        expected<Dns::Packet, Error> packet = Dns::Packet::makePacket(in_buf, in_len);

        if(!packet) {
            // TODO
            fprintf(stderr, "failed to parse packet: %s (%d)\n", packet.error().message.c_str(), packet.error().number);
        }

        in_id = packet->header.id;

        if(packet->header.qdcount != 1) {
            // TODO
            fprintf(stderr, "qd count is incorrect: %d\n", packet->header.qdcount);
        }

        auto question = packet->question();

        if(!question) {
            fprintf(stderr, "failed to parse question: %s (%d)\n", question.error().message.c_str(), question.error().number);
        }

        fprintf(stdout, "msg id: %d; dname: %s\n", in_id, question->qname.c_str()); 

        if((out_len = res_search(question->qname.c_str(), question->qclass, question->qtype, out_buf, sizeof(out_buf))) < 0) {
            // TODO
            fprintf(stderr, "failed to search: %s (%d)\n", strerror(errno), errno); 
        }

        if(ns_initparse(out_buf, out_len, &out_h) < 0) {
            // TODO
        }

        unsigned char *out_cp = (unsigned char *)ns_msg_base(out_h);
        ns_put16(in_id, out_cp);

        /*********************************/
        /* Send response to caller.      */
        /*********************************/
        socket.send_to(asio::buffer(out_buf, out_len), sender_endpoint);
    }

    return 0;
}
