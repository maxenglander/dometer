#include <iostream>
#include <stdlib.h>

#include "cwrap/resolv_wrapper/builder.hpp"
#include "cwrap/resolv_wrapper/resolv_wrapper.hpp"

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/libresolv_resolver.hpp"
#include "gtest/gtest.h"

namespace dometer::dns::resolver {
    class LibresolvResolverTest : public ::testing::Test {
        public:
            LibresolvResolverTest()
                :   _resolv_wrapper(cwrap::resolv_wrapper::builder::new_hosts_builder()
                        .add_a_record("hello.world", "1.2.3.4")
                        .add_a_record("goodbye.world", "4.3.2.1")
                        .build())
            {}
        private:
            const cwrap::resolv_wrapper::resolv_wrapper _resolv_wrapper;
    };

    TEST_F(LibresolvResolverTest, ResolvesValidQuery) {
        libresolv_resolver resolver(libresolv_function::query);

        auto resolve_result = resolver.resolve("hello.world", class_::in, type::a);
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
    }
}
