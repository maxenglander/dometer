#include <memory>
#include <stdexcept>

#include "dometer/dns/message/opcode.hpp"
#include "dometer/dns/message/question.hpp"
#include "dometer/dns/message/rcode.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/event/parse_query_event.hpp"
#include "dometer/dns/event/parse_reply_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/handler/resolving_handler.hpp"
#include "dometer/dns/message/builder.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/dns/record/class.hpp"
#include "dometer/dns/record/record.hpp"
#include "dometer/dns/record/type.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/resolver/error_code.hpp"
#include "dometer/dns/resolver/mock_resolver.hpp"
#include "dometer/event/mock_emitter.hpp"
#include "gtest/gtest.h"
#include "std/x/expected.hpp"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;
using ::testing::VariantWith;

namespace dometer::dns::handler {
    class ResolvingHandlerTest : public ::testing::Test {
        public:
            ResolvingHandlerTest()
                : _emitter(std::make_shared<dometer::event::mock_emitter<dometer::dns::event::any_event>>()),
                  _resolver(std::make_shared<dometer::dns::resolver::mock_resolver>()),
                  _resolving_handler(_emitter, _resolver)
            {}
        protected:
            std::shared_ptr<dometer::event::mock_emitter<dometer::dns::event::any_event>> _emitter;
            std::shared_ptr<dometer::dns::resolver::mock_resolver> _resolver;
            resolving_handler _resolving_handler;
    };

    TEST_F(ResolvingHandlerTest, EmitsAParseQueryEventIfQueryValid) {
        auto message = dometer::dns::message::builder()
            .add_question(dometer::dns::message::question{
                "hello.world", dometer::dns::record::type::a, dometer::dns::record::class_::in
            })
            .set_id(54321)
            .set_opcode(dometer::dns::message::opcode::query)
            .set_qr(dometer::dns::message::qr::query)
            .build();
        ASSERT_TRUE(message) << "Failed to create test message.";

        /* Set up catch-all */
        EXPECT_CALL(*_emitter, emit(_)).Times(AnyNumber());

        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::parse_query_event>(_))).Times(1);
        _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*message, (uint8_t*)*message + message->size()));
    }

    TEST_F(ResolvingHandlerTest, ErrorsIfInvalidQuery) {
        auto result = _resolving_handler.handle(0, std::vector<uint8_t>(8, 0));
        ASSERT_FALSE(result) << "Expected handler to reject invalid query.";
        ASSERT_EQ(result.error().code, error_code::invalid_query);
    }

    TEST_F(ResolvingHandlerTest, ResolvesQueryIfValid) {
        auto query = dometer::dns::message::builder()
            .add_question(dometer::dns::message::question{
                "hello.world", dometer::dns::record::type::a, dometer::dns::record::class_::in
            })
            .set_id(54321)
            .build();

        EXPECT_CALL(*_resolver, resolve);
        _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*query, (uint8_t*)*query + query->size()));
    }

    TEST_F(ResolvingHandlerTest, DoesNotResolveQueryIfInvalid) {
        auto query = dometer::dns::message::builder()
            .add_question(dometer::dns::message::question{
                "hello.world", dometer::dns::record::type::a, dometer::dns::record::class_::in
            })
            .set_id(54321)
            .set_opcode(dometer::dns::message::opcode::iquery)
            .build();

        EXPECT_CALL(*_resolver, resolve).Times(0);
        _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*query, (uint8_t*)*query + query->size()));
    }

    TEST_F(ResolvingHandlerTest, EmitsAResolveQueryEventIfQueryValid) {
        auto message = dometer::dns::message::builder()
            .add_question(dometer::dns::message::question{
                "hello.world", dometer::dns::record::type::a, dometer::dns::record::class_::in
            })
            .set_id(54321)
            .set_opcode(dometer::dns::message::opcode::query)
            .set_qr(dometer::dns::message::qr::query)
            .build();

        ASSERT_TRUE(message) << "Failed to create test message.";

        /* Set up catch-all */
        EXPECT_CALL(*_emitter, emit).Times(AnyNumber());

        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::parse_query_event>(_))).Times(1);
        _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*message, (uint8_t*)*message + message->size()));
    }

    TEST_F(ResolvingHandlerTest, EmitsParsesReplyEventIfResolverSucceeds) {
        auto query = dometer::dns::message::builder()
            .add_question(dometer::dns::message::question{
                "hello.world", dometer::dns::record::type::a, dometer::dns::record::class_::in
            })
            .set_id(54321)
            .set_opcode(dometer::dns::message::opcode::query)
            .set_qr(dometer::dns::message::qr::query)
            .build();

        auto reply = dometer::dns::message::builder()
            .add_question(dometer::dns::message::question{
                "hello.world", dometer::dns::record::type::a, dometer::dns::record::class_::in
            })
            .add_answer(dometer::dns::record::record{
                "hello.world", dometer::dns::record::type::a, dometer::dns::record::class_::in, 300, "80.70.60.50"
            })
            .set_id(54321)
            .set_opcode(dometer::dns::message::opcode::query)
            .set_qr(dometer::dns::message::qr::reply)
            .build();

        /* Set up catch-all */
        EXPECT_CALL(*_emitter, emit(_)).Times(AnyNumber());

        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::parse_reply_event>(_))).Times(1);
        EXPECT_CALL(*_resolver, resolve).Times(1)
            .WillOnce(Return(std::vector<uint8_t>((uint8_t*)*reply, (uint8_t*)*reply + reply->size())));
        _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*query, (uint8_t*)*query + query->size()));
    }

    TEST_F(ResolvingHandlerTest, DoesNotEmitParsesReplyEventIfResolverFails) {
        auto query = dometer::dns::message::builder()
            .add_question(dometer::dns::message::question{
                "hello.world", dometer::dns::record::type::a, dometer::dns::record::class_::in
            })
            .set_id(54321)
            .set_opcode(dometer::dns::message::opcode::query)
            .set_qr(dometer::dns::message::qr::query)
            .build();

        /* Set up catch-all */
        EXPECT_CALL(*_emitter, emit(_)).Times(AnyNumber());

        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::parse_reply_event>(_))).Times(0);
        EXPECT_CALL(*_resolver, resolve).Times(1)
            .WillOnce(Return(std::x::unexpected<dometer::dns::resolver::error>(
                dometer::dns::resolver::error(
                    "Resolver failure.",
                    dometer::dns::resolver::error_code::timedout
                )
            )));
        _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*query, (uint8_t*)*query + query->size()));
    }

    TEST_F(ResolvingHandlerTest, ReturnsNotImplIfUnsupportedOpcode) {
        auto query = dometer::dns::message::builder()
            .set_id(54321)
            .set_opcode(dometer::dns::message::opcode::iquery)
            .build();
        ASSERT_TRUE(query) << "Failed to create test query.";

        auto result = _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*query, (uint8_t*)*query + query->size()));
        ASSERT_TRUE(result) << result.error().message;

        auto reply = dometer::dns::message::parser::parse(*result);
        ASSERT_TRUE(reply) << reply.error().message;
        ASSERT_EQ(reply->get_rcode(), dometer::dns::message::rcode::notimpl);
    }
}
