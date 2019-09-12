#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <iostream>
#include <netdb.h>
#include <resolv.h>

#include "asio.hpp"

using namespace asio::ip;

int main(int argc, char **argv) {
    asio::io_context io_context;
    udp::socket socket(io_context, udp::endpoint(udp::v4(), 53));

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

        if(ns_initparse(in_buf, in_len, &in_h) < 0) {
            // TODO
        }

        in_id = ns_msg_id(in_h);

        if(ns_msg_count(in_h, ns_s_qd) != 1) {
            // TODO
        }

        if(ns_parserr(&in_h, ns_s_qd, 0, &in_qr) != 0) {
            // TODO
        }

        in_name = ns_rr_name(in_qr);
        in_class = ns_rr_class(in_qr);
        in_type = ns_rr_type(in_qr);

        fprintf(stdout, "msg id: %d; dname: %s\n", in_id, in_name); 

        if((out_len = res_search(in_name, in_class, in_type, out_buf, sizeof(out_buf))) < 0) {
            // TODO
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
