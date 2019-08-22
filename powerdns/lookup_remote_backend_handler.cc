#include <iostream>
#include <vector>

#include "json/json.h"
#include "powerdns/lookup_remote_backend_handler.h"
#include "powerdns/lookup_remote_backend_reply.h"
#include "powerdns/lookup_remote_backend_query.h"
#include "powerdns/remote_backend_handler.h"
#include "powerdns/remote_backend_replies.h"

namespace DnsTelemeter::PowerDns {
    Json::Value LookupRemoteBackendHandler::handle(Json::Value query) {
        if(!validate(query)) {
            return RemoteBackendReplies::failure();
        }

        Json::Value reply;
        reply["result"] = Json::arrayValue;

        std::string qtype = query["parameters"]["qtype"].asString();
        std::string qname = query["parameters"]["qname"].asString();

        std::vector<LookupRemoteBackendReply> lookupReply = handle(LookupRemoteBackendQuery(qtype, qname));

        for(std::vector<LookupRemoteBackendReply>::iterator it = lookupReply.begin(); it < lookupReply.end(); it++) {
            Json::Value entry;
            entry["qtype"] = qtype;
            entry["qname"] = qname;
            entry["content"] = (*it).content;
            entry["ttl"] = (*it).ttl;
            reply["result"].append(entry);
        }

        return reply;
    }

    bool LookupRemoteBackendHandler::validate(Json::Value query) {
        return query.isMember("parameters")
            && query["parameters"].isMember("qtype")
            && query["parameters"].isMember("qname")
            && query["parameters"]["qtype"].isString()
            && query["parameters"]["qname"].isString();
    }
}
