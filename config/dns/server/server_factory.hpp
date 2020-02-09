#pragma once

#include "config/dns/server/server.hpp"
#include "config/dns/server/transport_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::server {
    class ServerFactory {
        public:
            ServerFactory();
            ServerFactory(TransportFactory);
            Server fromJson(const rapidjson::Value& jsonValue) const;
        private:
            const TransportFactory transportFactory;
    };
}
