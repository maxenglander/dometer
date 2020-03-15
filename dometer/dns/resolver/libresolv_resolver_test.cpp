#include <iostream>
#include <memory>
#include <stdlib.h>

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/dns/handler/mock_handler.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/libresolv_resolver.hpp"
#include "dometer/dns/server/server.hpp"
#include "gtest/gtest.h"

namespace dometer::dns::resolver {
    class LibresolvResolverTest : public ::testing::Test {
        public:
            LibresolvResolverTest()
                : _handler(std::make_shared<dometer::dns::handler::mock_handler>()),
                  _server(std::static_pointer_cast<dometer::dns::handler::handler>(_handler))
            {}

            void SetUp() override {
                _server.start("127.0.0.1", 6353);
            }

            void TearDown() override {
                _server.join();
            }
        private:
            std::shared_ptr<dometer::dns::handler::mock_handler> _handler;
            dometer::dns::server::server _server;
    };

    TEST_F(LibresolvResolverTest, ResolvesValidQuery) {
        /*
        libresolv_resolver resolver(libresolv_function::query);

        auto resolve_result = resolver.resolve("xhello.world", class_::in, type::a);
        ASSERT_TRUE(resolve_result) << resolve_result.error().message;

        auto bytes = *resolve_result;
        auto parse_result = dometer::dns::message::parser::parse(bytes);
        ASSERT_TRUE(parse_result) << parse_result.error().message;

        auto answers = parse_result->get_answers();
        ASSERT_TRUE(answers) << answers.error().message;

        auto record = answers->front();
        ASSERT_EQ(record.name, "hello.world");
        ASSERT_EQ((std::string)record.type, "A");
        ASSERT_EQ(record.rdata, "1.2.3.4");
        */
    }
}
