#include <memory>
#include <stdexcept>

#include "dometer/dns/class.hpp"
#include "dometer/dns/opcode.hpp"
#include "dometer/dns/question.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/event/parse_query_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/handler/resolving_handler.hpp"
#include "dometer/dns/message/builder.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/resolver/error_code.hpp"
#include "dometer/dns/resolver/mock_resolver.hpp"
#include "dometer/event/mock_emitter.hpp"
#include "gtest/gtest.h"

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

    TEST_F(ResolvingHandlerTest, EmitsAParseQueryEvent) {
        auto message = dometer::dns::message::builder::new_builder()
            .add_question(dometer::dns::question{
                "hello.world", dometer::dns::type::a, dometer::dns::class_::in
            })
            .set_id(54321)
            .set_opcode(dometer::dns::opcode::query)
            .set_qr(dometer::dns::qr::query)
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
        auto query = dometer::dns::message::builder::new_builder()
            .add_question(dometer::dns::question{
                "hello.world", dometer::dns::type::a, dometer::dns::class_::in
            })
            .set_id(54321)
            .build();

        EXPECT_CALL(*_resolver, resolve);
        _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*query, (uint8_t*)*query + query->size()));
    }

    TEST_F(ResolvingHandlerTest, EmitsAResolveQueryEvent) {
        auto message = dometer::dns::message::builder::new_builder()
            .add_question(dometer::dns::question{
                "hello.world", dometer::dns::type::a, dometer::dns::class_::in
            })
            .set_id(54321)
            .set_opcode(dometer::dns::opcode::query)
            .set_qr(dometer::dns::qr::query)
            .build();

        ASSERT_TRUE(message) << "Failed to create test message.";

        /* Set up catch-all */
        EXPECT_CALL(*_emitter, emit).Times(AnyNumber());

        EXPECT_CALL(*_emitter, emit(VariantWith<dometer::dns::event::parse_query_event>(_))).Times(1);
        _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*message, (uint8_t*)*message + message->size()));
    }

    TEST_F(ResolvingHandlerTest, DoesNotResovleQueryIfInvalid) {
        auto query = dometer::dns::message::builder::new_builder()
            .add_question(dometer::dns::question{
                "hello.world", dometer::dns::type::a, dometer::dns::class_::in
            })
            .set_id(54321)
            .set_opcode(dometer::dns::opcode::iquery)
            .build();

        EXPECT_CALL(*_resolver, resolve).Times(0);
        _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*query, (uint8_t*)*query + query->size()));
    }

    TEST_F(ResolvingHandlerTest, ReturnsNotImplIfUnsupportedOpcode) {
        auto query = dometer::dns::message::builder::new_builder()
            .set_id(54321)
            .set_opcode(dometer::dns::opcode::iquery)
            .build();
        ASSERT_TRUE(query) << "Failed to create test query.";

        auto result = _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*query, (uint8_t*)*query + query->size()));
        ASSERT_TRUE(result) << result.error().message;

        auto reply = dometer::dns::message::parser::parse(*result);
        ASSERT_TRUE(reply) << reply.error().message;
        ASSERT_EQ(reply->get_rcode(), dometer::dns::rcode::notimpl);
    }
}
