#include "json/json.h"
#include "powerdns/remote_backend_replies.h"

namespace DnsTelemeter::PowerDns {
    Json::Value RemoteBackendReplies::failure() {
        Json::Value value;
        value["result"] = Json::Value(false);
        return value;
    }
}