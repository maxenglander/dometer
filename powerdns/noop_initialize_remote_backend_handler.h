#pragma once

#include "powerdns/initialize_remote_backend_handler.h"
#include "powerdns/initialize_remote_backend_query.h"

namespace DnsTelemeter::PowerDns {
    class NoopInitializeRemoteBackendHandler: public InitializeRemoteBackendHandler {
        public:
            NoopInitializeRemoteBackendHandler();
            bool handle(InitializeRemoteBackendQuery query) override;
    };
}
