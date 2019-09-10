#include "asio.hpp"

#define MAX_MESSAGE_SIZE 1024

using namespace asio::ip;

int main(int argc, char **argv) {
    asio::io_context io_context;
    udp::socket socket(io_context, udp::endpoint(udp::v4(), 53));

    for(;;) {
        char data[MAX_MESSAGE_SIZE];
        udp::endpoint sender_endpoint;

        size_t length = socket.receive_from(
            asio::buffer(data, MAX_MESSAGE_SIZE), sender_endpoint);

        socket.send_to(asio::buffer(data, length), sender_endpoint);
    }

    return 0;
}
