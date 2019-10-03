#include <iostream>

#include "experimental/expected.hpp"
#include "network/dns/server.hpp"

using namespace Dometer::Network;
using namespace std::experimental;

int main(int argc, char **argv) {
    Dns::Server server;
    auto result = server.serve();
    if(!result) {
        std::cerr << "failed to start DNS server: " + result.error().message
            + " (" + std::to_string(result.error().number) + ")" << std::endl;
        return 1;
    }
    return 0;
}
