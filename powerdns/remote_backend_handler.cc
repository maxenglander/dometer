#include "json/json.h"
#include "powerdns/remote_backend_handler.h"

namespace DnsTelemeter::PowerDns {
    Json::Value handle(Json::Value query) {
        Json::Value defaultReply;
        defaultReply["result"] = Json::Value(false);
        return defaultReply;
    }
}
