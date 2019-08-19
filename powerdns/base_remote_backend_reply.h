namespace DnsTelemeter::PowerDns {
    class BaseRemoteBackendReply {
        public:
            virtual Json::Value toJson();
    };
}
