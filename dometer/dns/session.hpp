namespace dometer::dns::session {
    class Recorder {
        public:
            Recorder(uint64_t sessionId);
            void recordQuery(std::expected<dometer::dns::message::message, dometer::util::error>);
            void recordQueryResolution();
            void recordReply(std::expected<dometer::dns::message::message, dometer::util::error>);
        private:
            const uint64_t sessionId;
    };
}
