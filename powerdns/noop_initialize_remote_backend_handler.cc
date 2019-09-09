#include "powerdns/initialize_remote_backend_query.h"
#include "powerdns/noop_initialize_remote_backend_handler.h"

namespace Dometer::PowerDns {
    NoopInitializeRemoteBackendHandler::NoopInitializeRemoteBackendHandler() {}

    bool NoopInitializeRemoteBackendHandler::handle(InitializeRemoteBackendQuery query) {
        return true;
    }
}
