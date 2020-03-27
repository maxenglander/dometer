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
#include "dometer/dns/metrics/lookup_summary.hpp"
#include "dometer/metrics/mock_recorder.hpp"
#include "dometer/metrics/summary.hpp"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AllOf;
using ::testing::Eq;
using ::testing::Field;
using ::testing::Matcher;
using ::testing::SaveArg;

namespace dometer::dns::eventmetrics {
    class MetricRecordingCallbackTest : public ::testing::Test {
        public:
            MetricRecordingCallbackTest()
                : _recorder(std::make_shared<dometer::metrics::mock_recorder>()),
                  _callback(_recorder)
            {}
        protected:
            std::shared_ptr<dometer::metrics::mock_recorder> _recorder;
            metric_recording_callback _callback;
    };

    Matcher<const dometer::metrics::summary&> IsALookupSummary() {
        return AllOf(
            Field(&dometer::metrics::summary::name, Eq(dometer::dns::metrics::lookup_summary::instance.name)),
            Field(&dometer::metrics::summary::description, Eq(dometer::dns::metrics::lookup_summary::instance.description)),
            Field(&dometer::metrics::summary::type, Eq(dometer::dns::metrics::lookup_summary::instance.type)),
            Field(&dometer::metrics::summary::unit, Eq(dometer::dns::metrics::lookup_summary::instance.unit))
        );
    }

    TEST_F(MetricRecordingCallbackTest, AfterACompletedSession_RecordsAnObservation) {
        EXPECT_CALL(*_recorder, record).Times(0);

        _callback(dometer::dns::event::start_session_event(54321));
        auto query = dometer::dns::message::message_factory::make_query(
            "hello.world", dometer::dns::type::a, dometer::dns::class_::in
        );
        _callback(dometer::dns::event::parse_query_event(54321, query));
        auto reply = dometer::dns::message::message_factory::make_reply(
            "hello.world", dometer::dns::type::a, dometer::dns::class_::in, 300, "80.70.60.50"
        );
        std::vector<uint8_t> reply_bytes((uint8_t*)*reply, (uint8_t*)*reply + reply->size());
        std::chrono::microseconds duration(1000);
        _callback(dometer::dns::event::resolve_query_event(54321, *(query->get_question()), reply_bytes, duration));
        _callback(dometer::dns::event::parse_query_event(54321, reply));

        EXPECT_CALL(*_recorder, record).Times(1);

        _callback(dometer::dns::event::stop_session_event(54321));
    }

    TEST_F(MetricRecordingCallbackTest, AfterACompletedSession_TheRecordedObservation_IsALookupSummary) {
        EXPECT_CALL(*_recorder, record(IsALookupSummary(), _, _));

        _callback(dometer::dns::event::start_session_event(54321));
        auto query = dometer::dns::message::message_factory::make_query(
            "hello.world", dometer::dns::type::a, dometer::dns::class_::in
        );
        _callback(dometer::dns::event::parse_query_event(54321, query));
        auto reply = dometer::dns::message::message_factory::make_reply(
            "hello.world", dometer::dns::type::a, dometer::dns::class_::in, 300, "80.70.60.50"
        );
        std::vector<uint8_t> reply_bytes((uint8_t*)*reply, (uint8_t*)*reply + reply->size());
        std::chrono::microseconds duration(1000);
        _callback(dometer::dns::event::resolve_query_event(54321, *(query->get_question()), reply_bytes, duration));
        _callback(dometer::dns::event::parse_query_event(54321, reply));
        _callback(dometer::dns::event::stop_session_event(54321));
    }

    TEST_F(MetricRecordingCallbackTest, AfterACompletedSession_WithoutResolveQueryEvent_DoesNotRecordAnObservation) {
        EXPECT_CALL(*_recorder, record).Times(0);

        _callback(dometer::dns::event::start_session_event(54321));
        auto query = dometer::dns::message::message_factory::make_query(
            "hello.world", dometer::dns::type::a, dometer::dns::class_::in
        );
        _callback(dometer::dns::event::parse_query_event(54321, query));
        auto reply = dometer::dns::message::message_factory::make_reply(
            "hello.world", dometer::dns::type::a, dometer::dns::class_::in, 300, "80.70.60.50"
        );
        _callback(dometer::dns::event::parse_query_event(54321, reply));
        _callback(dometer::dns::event::stop_session_event(54321));
    }
}
