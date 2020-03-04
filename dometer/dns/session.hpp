namespace dometer::dns::session {
    class Recorder {
        public:
            Recorder(uint64_t sessionId);
            void recordQuery(std::expected<dometer::dns::message::Message, dometer::util::Error>);
            void recordQueryResolution();
            void recordReply(std::expected<dometer::dns::message::Message, dometer::util::Error>);
        private:
            const uint64_t sessionId;
    };
}
