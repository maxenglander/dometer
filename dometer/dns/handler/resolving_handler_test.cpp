#include <memory>

#include "dometer/dns/opcode.hpp"
#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/handler/resolving_handler.hpp"
#include "dometer/dns/message/builder.hpp"
#include "dometer/dns/resolver/error_code.hpp"
#include "dometer/dns/resolver/mock_resolver.hpp"
#include "dometer/event/mock_emitter.hpp"
#include "gtest/gtest.h"

namespace dometer::dns::handler {
    class ResolvingHandlerTest : public ::testing::Test {
        public:
            ResolvingHandlerTest()
                : _emitter(),
                  _resolver(std::make_shared<dometer::dns::resolver::mock_resolver>(dometer::dns::resolver::mock_resolver())),
                  _resolving_handler(_emitter,
                                     std::static_pointer_cast<dometer::dns::resolver::resolver>(_resolver))
            {}
        protected:
            dometer::event::mock_emitter<dometer::dns::event::any_event> _emitter;
            std::shared_ptr<dometer::dns::resolver::mock_resolver> _resolver;
            resolving_handler _resolving_handler;
    };

    TEST_F(ResolvingHandlerTest, ErrorsIfInvalidQuery) {
        auto result = _resolving_handler.handle(0, std::vector<uint8_t>(8, 0));
        ASSERT_FALSE(result) << "Expected handler to reject invalid query.";
        ASSERT_EQ(result.error().code, error_code::INVALID_QUERY);
    }

    TEST_F(ResolvingHandlerTest, ReturnsNotImplIfUnsupportedOpcode) {
        auto message = dometer::dns::message::builder::new_builder()
            .set_id(54321)
            .set_opcode(dometer::dns::opcode::iquery)
            .build();
        ASSERT_TRUE(message) << "Failed to create test message.";

        auto result = _resolving_handler.handle(0, std::vector<uint8_t>((uint8_t*)*message, (uint8_t*)*message + message->size()));
        ASSERT_TRUE(result) << result.error().message;
    }
}
