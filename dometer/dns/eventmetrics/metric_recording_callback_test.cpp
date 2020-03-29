#include <chrono>
#include <map>
#include <memory>
#include <vector>

#include "dometer/dns/class.hpp"
#include "dometer/dns/opcode.hpp"
#include "dometer/dns/qr.hpp"
#include "dometer/dns/question.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/event/parse_query_event.hpp"
#include "dometer/dns/event/parse_reply_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/event/start_session_event.hpp"
#include "dometer/dns/event/stop_session_event.hpp"
#include "dometer/dns/eventmetrics/metric_recording_callback.hpp"
#include "dometer/dns/message/message_factory.hpp"
#include "dometer/dns/metrics/lookup_summary.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/resolver/error_code.hpp"
#include "dometer/metrics/mock_recorder.hpp"
#include "dometer/metrics/summary.hpp"
#include "gtest/gtest.h"
#include "std/x/expected.hpp"

using ::testing::_;
using ::testing::AllOf;
using ::testing::Contains;
using ::testing::Eq;
using ::testing::Field;
using ::testing::Key;
using ::testing::IsSupersetOf;
using ::testing::Matcher;
using ::testing::SaveArg;

namespace dometer::dns::eventmetrics {
    class metric_recording_callback_client {
        public:
            metric_recording_callback_client(metric_recording_callback& callback)
                : _callback(callback)
            {}
            void parse_query(uint64_t session_id, std::string qname, dometer::dns::type qtype, dometer::dns::class_ qclass) {
                _callback(dometer::dns::event::parse_query_event(session_id, dometer::dns::message::message_factory::make_query(
                    qname, qtype, qclass
                )));
            }
            void parse_reply(uint64_t session_id, std::string qname, dometer::dns::type qtype,
                             dometer::dns::class_ qclass, int ttl, std::string rdata) {
                auto reply = dometer::dns::message::message_factory::make_reply(
                    qname, qtype, qclass, ttl, rdata
                );
                _callback(dometer::dns::event::parse_reply_event(session_id, reply));
            }
            void resolve_query(uint64_t session_id, std::string qname, dometer::dns::type qtype,
                               dometer::dns::class_ qclass, int ttl, std::string rdata, uint64_t duration_us) {
                auto reply = dometer::dns::message::message_factory::make_reply(
                    qname, qtype, qclass, ttl, rdata
                );
                std::vector<uint8_t> reply_bytes((uint8_t*)*reply, (uint8_t*)*reply + reply->size());
                std::chrono::microseconds duration(duration_us);
                _callback(dometer::dns::event::resolve_query_event(session_id, *(reply->get_question()), reply_bytes, duration));
            }
            void resolve_query(uint64_t session_id, std::string qname, dometer::dns::type qtype,
                               dometer::dns::class_ qclass, dometer::dns::resolver::error error, uint64_t duration_us) {
                dometer::dns::question question{qname, qtype, qclass};
                std::chrono::microseconds duration(duration_us);
                _callback(dometer::dns::event::resolve_query_event(session_id, question,
                                                                   std::x::unexpected<dometer::dns::resolver::error>(error),
                                                                   duration));
            }
            void start_session(uint64_t session_id) {
                _callback(dometer::dns::event::start_session_event(session_id));
            }
            void stop_session(uint64_t session_id) {
                _callback(dometer::dns::event::stop_session_event(session_id));
            }
        protected:
            metric_recording_callback& _callback;
    };

    class MetricRecordingCallbackTest : public ::testing::Test {
        public:
            MetricRecordingCallbackTest()
                : _recorder(std::make_shared<dometer::metrics::mock_recorder>()),
                  _callback(_recorder),
                  _client(_callback)
            {}
        protected:
            std::shared_ptr<dometer::metrics::mock_recorder> _recorder;
            metric_recording_callback _callback;
            metric_recording_callback_client _client;
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

        _client.start_session(54321);
        _client.parse_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in);
        _client.resolve_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50", 1000);
        _client.parse_reply(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50");

        EXPECT_CALL(*_recorder, record).Times(1);

        _client.stop_session(54321);
    }

    TEST_F(MetricRecordingCallbackTest, AfterACompletedSession_TheRecordedObservation_IsALookupSummary) {
        EXPECT_CALL(*_recorder, record(IsALookupSummary(), _, _));

        _client.start_session(54321);
        _client.parse_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in);
        _client.resolve_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50", 1000);
        _client.parse_reply(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50");
        _client.stop_session(54321);
    }

    TEST_F(MetricRecordingCallbackTest, AfterACompletedSession_TheRecordedObservation_HasQueryLabels) {
        EXPECT_CALL(*_recorder, record(_, IsSupersetOf(std::map<std::string, std::string>({
            {"qname", "hello.world"}, {"qtype", dometer::dns::type::a}, {"qclass", dometer::dns::class_::in}
        })), _));

        _client.start_session(54321);
        _client.parse_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in);
        _client.resolve_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50", 1000);
        _client.parse_reply(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50");
        _client.stop_session(54321);
    }

    TEST_F(MetricRecordingCallbackTest, AfterACompletedSession_TheRecordedObservation_HasRcodeLabel) {
        EXPECT_CALL(*_recorder, record(_, IsSupersetOf(std::map<std::string, std::string>({
            {"rcode", dometer::dns::rcode::noerror}
        })), _));

        _client.start_session(54321);
        _client.parse_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in);
        _client.resolve_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50", 1000);
        _client.parse_reply(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50");
        _client.stop_session(54321);
    }

    TEST_F(MetricRecordingCallbackTest, AfterACompletedSession_TheRecordedObservation_HasEmptyErrorLabel) {
        EXPECT_CALL(*_recorder, record(_, IsSupersetOf(std::map<std::string, std::string>({
            {"error", "-"}
        })), _));

        _client.start_session(54321);
        _client.parse_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in);
        _client.resolve_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50", 1000);
        _client.parse_reply(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50");
        _client.stop_session(54321);
    }

    TEST_F(MetricRecordingCallbackTest, AfterACompletedSession_TheRecordedObservation_HasExpectedDuration) {
        EXPECT_CALL(*_recorder, record(_, _, (double)1000/1000000));

        _client.start_session(54321);
        _client.parse_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in);
        _client.resolve_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50", 1000);
        _client.parse_reply(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50");
        _client.stop_session(54321);
    }

    TEST_F(MetricRecordingCallbackTest, AfterACompletedSession_WithResolverError_TheRecordedObservation_HasExpectedErrorLabel) {
        EXPECT_CALL(*_recorder, record(_, IsSupersetOf(std::map<std::string, std::string>({
            {"error", "CONNREFUSED"}
        })), _));

        _client.start_session(54321);
        _client.parse_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in);
        _client.resolve_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in,
                              dometer::dns::resolver::error("Resolver error.", dometer::dns::resolver::error_code::connrefused),
                              1000);
        _client.stop_session(54321);
    }

    TEST_F(MetricRecordingCallbackTest, AfterACompletedSession_WithoutResolveQueryEvent_DoesNotRecordAnObservation) {
        EXPECT_CALL(*_recorder, record).Times(0);

        _client.start_session(54321);
        _client.parse_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in);
        //_client.resolve_query(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50", 1000);
        _client.parse_reply(54321, "hello.world", dometer::dns::type::a, dometer::dns::class_::in , 300, "80.70.60.50");
        _client.stop_session(54321);
    }
}