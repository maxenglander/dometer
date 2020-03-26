#include <chrono>
#include <memory>
#include <vector>

#include "dometer/dns/class.hpp"
#include "dometer/dns/opcode.hpp"
#include "dometer/dns/qr.hpp"
#include "dometer/dns/question.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/event/parse_query_event.hpp"
#include "dometer/dns/event/parse_reply_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/event/start_session_event.hpp"
#include "dometer/dns/event/stop_session_event.hpp"
#include "dometer/dns/eventmetrics/metric_recording_callback.hpp"
#include "dometer/dns/message/message_factory.hpp"
#include "dometer/metrics/mock_recorder.hpp"
#include "gtest/gtest.h"

namespace dometer::dns::eventmetrics {
    class MetricRecordingCallbackTest : public testing::Test {
        public:
            MetricRecordingCallbackTest()
                : _recorder(std::make_shared<dometer::metrics::mock_recorder>()),
                  _callback(_recorder)
            {}
        protected:
            std::shared_ptr<dometer::metrics::mock_recorder> _recorder;
            metric_recording_callback _callback;
    };

    TEST_F(MetricRecordingCallbackTest, RecordsALookupAfterACompleteSession) {
        EXPECT_CALL(*_recorder, record).Times(0);

        _callback(dometer::dns::event::start_session_event(54321));

        auto query = dometer::dns::message::message_factory::make_query(
            "hello.world", dometer::dns::type::a, dometer::dns::class_::in
        );
        ASSERT_TRUE(query) << query.error().message;

        _callback(dometer::dns::event::parse_query_event(54321, query));

        auto reply = dometer::dns::message::message_factory::make_reply(
            "hello.world", dometer::dns::type::a, dometer::dns::class_::in, 300, "80.70.60.50"
        );
        ASSERT_TRUE(reply) << reply.error().message;

        std::vector<uint8_t> reply_bytes((uint8_t*)*reply, (uint8_t*)*reply + reply->size());
        std::chrono::microseconds duration(1000);
        _callback(dometer::dns::event::resolve_query_event(54321, *(query->get_question()), reply_bytes, duration));

        _callback(dometer::dns::event::parse_query_event(54321, reply));

        EXPECT_CALL(*_recorder, record).Times(1);

        _callback(dometer::dns::event::stop_session_event(54321));
    }

    TEST_F(MetricRecordingCallbackTest, DoesNotRecordALookupWithoutResolvQueryEvent) {
        EXPECT_CALL(*_recorder, record).Times(0);

        _callback(dometer::dns::event::start_session_event(54321));

        auto query = dometer::dns::message::message_factory::make_query(
            "hello.world", dometer::dns::type::a, dometer::dns::class_::in
        );
        ASSERT_TRUE(query) << query.error().message;

        _callback(dometer::dns::event::parse_query_event(54321, query));

        auto reply = dometer::dns::message::message_factory::make_reply(
            "hello.world", dometer::dns::type::a, dometer::dns::class_::in, 300, "80.70.60.50"
        );
        ASSERT_TRUE(reply) << reply.error().message;

        _callback(dometer::dns::event::parse_query_event(54321, reply));

        _callback(dometer::dns::event::stop_session_event(54321));
    }
}
