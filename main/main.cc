#include <memory>

#include "network/dns/native_resolver.h"
#include "network/socket/unix_socket.h"
#include "powerdns/native_lookup_remote_backend_handler.h"
#include "powerdns/remote_backend_router.h"
#include "powerdns/unix_socket_remote_backend.h"
#include "std/experimental/expected.h"
#include "util/json_serde.h"

#define MAX_MESSAGE_SIZE 4096
#define MAX_CONNECTIONS  100
#define SOCKET_PATH      "/var/run/dns-telemeter.sock"

using namespace DnsTelemeter;
using namespace DnsTelemeter::Network::Socket;
using namespace std::experimental;

int main(int argc, char **argv) {
    Util::JsonSerde jsonSerde;
    Network::Dns::NativeResolver dnsNativeResolver;
    std::shared_ptr<PowerDns::NativeLookupRemoteBackendHandler> lookupHandler
        = std::make_shared<PowerDns::NativeLookupRemoteBackendHandler>(dnsNativeResolver);
    PowerDns::RemoteBackendRouter router;
    router.on("lookup", lookupHandler);
    PowerDns::UnixSocketRemoteBackend pdnsBackend(
        jsonSerde,
        MAX_CONNECTIONS,
        MAX_MESSAGE_SIZE,
        router,
        std::string(SOCKET_PATH)
    );
    pdnsBackend.serve();
    return 0;
}
