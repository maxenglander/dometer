#include <iostream>
#include <memory>

#include "experimental/expected.hpp"
#include "network/dns/server/event_type.hpp"
#include "network/dns/server/native_resolving_handler.hpp"
#include "network/dns/server/server.hpp"

using namespace Dometer::Network;
using namespace std::experimental;

int main(int argc, char **argv) {
    auto handler = std::make_unique<Dns::Server::NativeResolvingHandler>();
    Dns::Server::Server server(std::move(handler));
    auto result = server.serve();

    if(!result) {
        std::cerr << "failed to start DNS server: " + result.error().message
            + " (" + std::to_string(result.error().number) + ")" << std::endl;
        return 1;
    }

    return 0;
}
