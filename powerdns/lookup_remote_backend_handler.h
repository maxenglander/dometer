#pragma once

#include <vector>

#include "json/json.h"
#include "powerdns/lookup_remote_backend_query.h"
#include "powerdns/lookup_remote_backend_reply.h"
#include "powerdns/remote_backend_handler.h"

namespace DnsTelemeter::PowerDns {
    class LookupRemoteBackendHandler: public RemoteBackendHandler {
        public:
            virtual Json::Value handle(Json::Value query) override final;
            virtual std::vector<LookupRemoteBackendReply> handle(LookupRemoteBackendQuery query) = 0;
        private:
            bool validate(Json::Value query);
    };
}
