#include "config/dns/server/server.hpp"
#include "config/dns/server/server_factory.hpp"
#include "config/dns/server/transport.hpp"
#include "config/dns/server/transport_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::server {
    ServerFactory::ServerFactory() : ServerFactory::ServerFactory(TransportFactory()) {}
    ServerFactory::ServerFactory(TransportFactory transportFactory) : transportFactory(transportFactory) {}

    Server ServerFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("transport"));
        assert(jsonValue["transport"].IsObject());
        return Server{
            transportFactory.fromJson(jsonValue["transport"])
        };
    }
}
