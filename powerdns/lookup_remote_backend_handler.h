#pragma once

#include <vector>

#include "json/json.h"
#include "powerdns/lookup_query.h"
#include "powerdns/lookup_reply.h"
#include "powerdns/remote_backend_handler.h"

namespace DnsTelemeter::PowerDns {
    class LookupRemoteBackendHandler: public RemoteBackendHandler {
        public:
            Json::Value handle(Json::Value query) final;
        protected:
            virtual std::vector<LookupReply> handle(LookupQuery query) const = 0;
        private:
            bool validate(Json::Value query);
    };
}
