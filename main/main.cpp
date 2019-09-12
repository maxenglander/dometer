#include <iostream>

#include "asio.hpp"
#include "ldns/ldns.h"

#define MAX_MESSAGE_SIZE 1024

using namespace asio::ip;

int main(int argc, char **argv) {
    asio::io_context io_context;
    udp::socket socket(io_context, udp::endpoint(udp::v4(), 53));

    for(;;) {
        unsigned char* answer_buf;
        ldns_rr_list *answer_ad;
        ldns_rr_list *answer_an;
        size_t answer_len;
        ldns_rr_list *answer_ns;
        ldns_pkt *answer_pkt;
        ldns_rr_list *answer_qr;

        unsigned char query_buf[MAX_MESSAGE_SIZE];
        size_t query_len;
        ldns_pkt *query_pkt;
        ldns_rr_list *query_qr;

        udp::endpoint sender_endpoint;
        query_len = socket.receive_from(
            asio::buffer(query_buf, MAX_MESSAGE_SIZE), sender_endpoint);

        /*********************************/
        /* Convert received message to   */
        /* DNS query packet structure.   */
        /*********************************/
        if(ldns_wire2pkt(&query_pkt, query_buf, query_len) != LDNS_STATUS_OK) {
            // TODO
            std::cout << "Failed to create packet model from wire" << std::endl;
        }

        /*********************************/
        /* Initialize answer packet.     */
        /*********************************/
        answer_pkt = ldns_pkt_new();
        ldns_pkt_set_qr(answer_pkt, 1);
        ldns_pkt_set_id(answer_pkt, ldns_pkt_id(query_pkt));

        /*********************************/
        /* Loop over question records.   */
        /*********************************/
        answer_qr = ldns_rr_list_new();
        query_qr = ldns_pkt_question(query_pkt);

        for(size_t i = 0; i < ldns_rr_list_rr_count(query_qr); i++) {
            ldns_rr *query_rr = ldns_rr_list_rr(query_qr, i);
            ldns_rr_list_push_rr(answer_qr, ldns_rr_clone(query_rr));
        }

        answer_ad = ldns_rr_list_new();
        answer_an = ldns_rr_list_new();
        answer_ns = ldns_rr_list_new();

        /*********************************/
        /* Attach sections to answer.    */
        /*********************************/
        ldns_pkt_push_rr_list(answer_pkt, LDNS_SECTION_ADDITIONAL, answer_ad);
        ldns_pkt_push_rr_list(answer_pkt, LDNS_SECTION_ANSWER, answer_an);
        ldns_pkt_push_rr_list(answer_pkt, LDNS_SECTION_AUTHORITY, answer_ns);
        ldns_pkt_push_rr_list(answer_pkt, LDNS_SECTION_QUESTION, answer_qr);

        /*********************************/
        /* Serialize answer packet       */
        /* structure.                    */
        /*********************************/
        if(ldns_pkt2wire(&answer_buf, answer_pkt, &answer_len) != LDNS_STATUS_OK) {
            // TODO
            std::cout << "Failed to serialize packet model to wire format" << std::endl;
        }

        /*********************************/
        /* Send response to caller.      */
        /*********************************/
        socket.send_to(asio::buffer(answer_buf, answer_len), sender_endpoint);

        /*********************************/
        /* Free memory. Order matters.   */
        /*********************************/
        ldns_pkt_free(query_pkt);

        LDNS_FREE(answer_buf);
        ldns_pkt_free(answer_pkt);
        ldns_rr_list_free(answer_qr);
        ldns_rr_list_free(answer_an);
        ldns_rr_list_free(answer_ns);
        ldns_rr_list_free(answer_ad);
    }

    return 0;
}
