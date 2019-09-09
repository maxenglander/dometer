#pragma once

namespace Dometer::PowerDns {
    class RemoteBackend {
        private:
            Json::Value handleQuery(Json::Value);
    };
}
