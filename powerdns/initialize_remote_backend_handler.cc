#include <iostream>
#include <vector>
#include <stdexcept>

#include "json/json.h"
#include "powerdns/initialize_remote_backend_handler.h"
#include "powerdns/initialize_remote_backend_query.h"
#include "powerdns/remote_backend_handler.h"
#include "powerdns/remote_backend_replies.h"

namespace DnsTelemeter::PowerDns {
    Json::Value InitializeRemoteBackendHandler::handle(Json::Value query) {
        if(!validate(query)) {
            return RemoteBackendReplies::failure();
        }

        std::string command = query["parameters"]["command"].asString();

        int timeout;
        try {
            timeout = stoi(query["parameters"]["timeout"].asString());
        } catch(const std::invalid_argument& e) {
            return RemoteBackendReplies::failure();
        } catch(const std::out_of_range& e) {
            return RemoteBackendReplies::failure();
        }

        return handle(InitializeRemoteBackendQuery{command, timeout});
    }

    bool InitializeRemoteBackendHandler::validate(Json::Value query) {
        return query.isMember("parameters")
            && query["parameters"].isMember("command")
            && query["parameters"].isMember("timeout")
            && query["parameters"]["command"].isString()
            && query["parameters"]["timeout"].isString();
    }
}
