#include <memory>
#include <string>

#include "dometer/dns/class.hpp"
#include "dometer/dns/opcode.hpp"
#include "dometer/dns/qr.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/event/start_session_event.hpp"
#include "dometer/dns/event/stop_session_event.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/handler/mock_handler.hpp"
#include "dometer/dns/message/builder.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/resolver/libresolv_helper.hpp"
#include "dometer/dns/resolver/libresolv_resolver.hpp"
#include "dometer/event/mock_emitter.hpp"
#include "dometer/dns/server/server.hpp"

#include "gtest/gtest.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::InSequence;
using ::testing::VariantWith;

namespace dometer::dns::server {
    class ServerTest : public ::testing::Test {
        public:
            ServerTest()
                : _emitter(std::make_shared<dometer::event::mock_emitter<dometer::dns::event::any_event>>()),
                  _handler(std::make_shared<dometer::dns::handler::mock_handler>()),
                  _server(_emitter, _handler)
            {}
        protected:
            std::shared_ptr<dometer::event::mock_emitter<dometer::dns::event::any_event>> _emitter;
            std::shared_ptr<dometer::dns::handler::mock_handler> _handler;
            server _server;
    };

    class AutoServerTest : public ServerTest {
        public:
            void SetUp() {
                _server.start("127.0.0.1", 6353);
            }
            void TearDown() {
                _server.stop();
            }
    };

    TEST_F(ServerTest, StartsAndStops) {
        _server.start("127.0.0.1", 6353);
        _server.stop();
    }

    TEST_F(AutoServerTest, ReceivesAndHandlesRequests) {
        auto message = dometer::dns::message::builder::new_builder()
            .set_id(54321)
            .set_qr(dometer::dns::qr::query)
            .set_opcode(dometer::dns::opcode::query)
            .build();

        ASSERT_TRUE(message) << message.error().message;

        EXPECT_CALL(*_handler, handle).WillOnce(Invoke(&dometer::dns::handler::mock_handler::return_nxdomain));

        auto resolver = dometer::dns::resolver::libresolv_resolver(
                dometer::dns::resolver::libresolv_helper::make_res_state_for_nameserver("127.0.0.1", 6353));
        auto resolve_result = resolver.resolve("hello.world", dometer::dns::class_::in, dometer::dns::type::a);
        ASSERT_TRUE(resolve_result) << resolve_result.error().message;
    }

    TEST_F(AutoServerTest, EmitsAStartAndStopSessionEvent) {
        InSequence s;

        auto message = dometer::dns::message::builder::new_builder()
            .set_id(54321)
            .set_qr(dometer::dns::qr::query)
            .set_opcode(dometer::dns::opcode::query)
            .build();

        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::start_session_event>(_)));
        EXPECT_CALL(*_handler, handle).WillOnce(Invoke(&dometer::dns::handler::mock_handler::return_nxdomain));
        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::stop_session_event>(_)));

        auto resolver = dometer::dns::resolver::libresolv_resolver(
                dometer::dns::resolver::libresolv_helper::make_res_state_for_nameserver("127.0.0.1", 6353));
        resolver.resolve("hello.world", dometer::dns::class_::in, dometer::dns::type::a);
    }
}
