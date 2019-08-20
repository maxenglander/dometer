#include <string>
#include <unordered_map>

#include "json/json.h"
#include "powerdns/remote_backend_handler.h"
#include "powerdns/remote_backend_router.h"
#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::PowerDns {
    RemoteBackendRouter::RemoteBackendRouter() {
        handlers = std::unordered_map<std::string, RemoteBackendHandler>();
    }

    void RemoteBackendRouter::on(std::string method, RemoteBackendHandler handler) {
        handlers[method] = handler;
    }

    Json::Value RemoteBackendRouter::route(Json::Value query) {
        Json::Value failure;
        failure["result"] = Json::Value(false);

        if(!query.isMember("method"))
            return failure;

        Json::Value method = query["method"];

        if(!method.isString())
            return failure;

        auto search = handlers.find(method.asString());

        if(search == handlers.end())
            return failure;

        auto key = search->first;
        return handlers[key].handle(query);
    }
}
