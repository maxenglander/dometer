#include <vector>

#include "json/json.h"
#include "powerdns/lookup_remote_backend_handler.h"
#include "powerdns/lookup_reply.h"
#include "powerdns/lookup_query.h"

namespace DnsTelemeter::PowerDns {
    Json::Value LookupRemoteBackendHandler::handle(Json::Value query) {
        if(!validate(query))
            return RemoteBackendHandler::handle(query);

        Json::Value reply;
        reply["result"] = Json::arrayValue;

        std::string qtype = query["parameters"]["qtype"].asString();
        std::string qname = query["parameters"]["qname"].asString();

        std::vector<LookupReply> lookupReply = this->handle(LookupQuery(qtype, qname));

        for(std::vector<LookupReply>::iterator it = lookupReply.begin(); it < lookupReply.end(); it++) {
            Json::Value entry(query);
            entry["content"] = (*it).content;
            entry["ttl"] = (*it).ttl;
            reply["result"].append(entry);
        }

        return reply;
    }

    bool LookupRemoteBackendHandler::validate(Json::Value query) {
        return query.isMember("parameters")
            && query["parameters"].isMember("qtype")
            && query["parameters"].isMember("name")
            && query["parameters"]["qtype"].isString()
            && query["parameters"]["qname"].isString();
    }
}
