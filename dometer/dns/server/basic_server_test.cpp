#include <memory>
#include <string>

#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/event/start_session_event.hpp"
#include "dometer/dns/event/stop_session_event.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/handler/mock_handler.hpp"
#include "dometer/dns/message/builder.hpp"
#include "dometer/dns/message/opcode.hpp"
#include "dometer/dns/message/qr.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/record/class.hpp"
#include "dometer/dns/record/type.hpp"
#include "dometer/dns/resolver/libresolv_helper.hpp"
#include "dometer/dns/resolver/libresolv_resolver.hpp"
#include "dometer/event/mock_emitter.hpp"
#include "dometer/dns/server/basic_server.hpp"

#include "gtest/gtest.h"

using ::testing::_;
using ::testing::Eq;
using ::testing::Invoke;
using ::testing::InSequence;
using ::testing::Property;
using ::testing::VariantWith;

namespace dometer::dns::server {
    class BasicServerTest : public ::testing::Test {
        public:
            BasicServerTest()
                : _emitter(std::make_shared<dometer::event::mock_emitter<dometer::dns::event::any_event>>()),
                  _handler(std::make_shared<dometer::dns::handler::mock_handler>()),
                  _server(_emitter, _handler)
            {}
        protected:
            std::shared_ptr<dometer::event::mock_emitter<dometer::dns::event::any_event>> _emitter;
            std::shared_ptr<dometer::dns::handler::mock_handler> _handler;
            basic_server _server;
    };

    class AutoBasicServerTest : public BasicServerTest {
        public:
            void SetUp() {
                _server.start("127.0.0.1:6353");
            }
            void TearDown() {
                _server.stop();
            }
    };

    TEST_F(BasicServerTest, StartsAndStops) {
        _server.start("127.0.0.1:6353");
        _server.stop();
    }

    TEST_F(AutoBasicServerTest, ReceivesAndHandlesRequests) {
        auto message = dometer::dns::message::builder()
            .set_id(54321)
            .set_qr(dometer::dns::message::qr::query)
            .set_opcode(dometer::dns::message::opcode::query)
            .build();

        ASSERT_TRUE(message) << message.error().message;

        EXPECT_CALL(*_handler, handle).WillOnce(Invoke(&dometer::dns::handler::mock_handler::return_nxdomain));

        auto resolver = dometer::dns::resolver::libresolv_resolver(
                dometer::dns::resolver::libresolv_helper::make_res_state_for_nameserver("127.0.0.1", 6353));
        auto resolve_result = resolver.resolve("hello.world", dometer::dns::record::class_::in, dometer::dns::record::type::a);
        ASSERT_TRUE(resolve_result) << resolve_result.error().message;
    }

    TEST_F(AutoBasicServerTest, EmitsAStartAndStopSessionEvent) {
        InSequence s;

        auto message = dometer::dns::message::builder()
            .set_id(54321)
            .set_qr(dometer::dns::message::qr::query)
            .set_opcode(dometer::dns::message::opcode::query)
            .build();

        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::start_session_event>(_)));
        EXPECT_CALL(*_handler, handle).WillOnce(Invoke(&dometer::dns::handler::mock_handler::return_nxdomain));
        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::stop_session_event>(_)));

        auto resolver = dometer::dns::resolver::libresolv_resolver(
                dometer::dns::resolver::libresolv_helper::make_res_state_for_nameserver("127.0.0.1", 6353));
        resolver.resolve("hello.world", dometer::dns::record::class_::in, dometer::dns::record::type::a);
    }

    TEST_F(AutoBasicServerTest, IncrementsSessionCounterBetweenCalls) {
        InSequence s;

        auto message = dometer::dns::message::builder()
            .set_id(54321)
            .set_qr(dometer::dns::message::qr::query)
            .set_opcode(dometer::dns::message::opcode::query)
            .build();

        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::start_session_event>(
            Property(&dometer::dns::event::start_session_event::get_session_id, Eq(0))
        )));
        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::stop_session_event>(
            Property(&dometer::dns::event::stop_session_event::get_session_id, Eq(0))
        )));
        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::start_session_event>(
            Property(&dometer::dns::event::start_session_event::get_session_id, Eq(1))
        )));
        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::stop_session_event>(
            Property(&dometer::dns::event::stop_session_event::get_session_id, Eq(1))
        )));

        auto resolver = dometer::dns::resolver::libresolv_resolver(
                dometer::dns::resolver::libresolv_helper::make_res_state_for_nameserver("127.0.0.1", 6353));
        resolver.resolve("hello.world", dometer::dns::record::class_::in, dometer::dns::record::type::a);
        resolver.resolve("hello.world", dometer::dns::record::class_::in, dometer::dns::record::type::a);
    }
}
