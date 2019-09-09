#include <iostream>
#include <stdexcept>

#include "json/json.h"
#include "powerdns/initialize_remote_backend_handler.h"
#include "powerdns/remote_backend_handler.h"
#include "powerdns/remote_backend_replies.h"

namespace Dometer::PowerDns {
    Json::Value InitializeRemoteBackendHandler::handle(Json::Value query) {
        if(!validate(query)) {
            return RemoteBackendReplies::failure();
        }

        std::string path = query["parameters"]["path"].asString();

        int timeout = 2000;
        if(query["parameters"].isMember("timeout")) {
            try {
                timeout = stoi(query["parameters"]["timeout"].asString());
            } catch(const std::invalid_argument& e) {
                return RemoteBackendReplies::failure();
            } catch(const std::out_of_range& e) {
                return RemoteBackendReplies::failure();
            }
        }

        if(handle(InitializeRemoteBackendQuery{path, timeout})) {
            return RemoteBackendReplies::success();
        } else {
            return RemoteBackendReplies::failure();
        }
    }

    bool InitializeRemoteBackendHandler::validate(Json::Value query) {
        if(!query.isMember("parameters")
            || !query["parameters"].isMember("path")
            || !query["parameters"]["path"].isString())
            return false;

        if(query["parameters"].isMember("timeout"))
            return query["parameters"]["timeout"].isString();

        return true;
    }
}
