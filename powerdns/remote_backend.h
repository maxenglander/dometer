#pragma once

namespace DnsTelemeter::PowerDns {
    class RemoteBackend {
        private:
            Json::Value handleQuery(Json::Value);
    };
}
