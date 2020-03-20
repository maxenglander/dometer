#include <arpa/nameser.h>
#include <resolv.h>

#include "dometer/dns/qr.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/message/builder.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/util/human_error_encoder.hpp"
#include "gtest/gtest.h"

namespace dns = dometer::dns;

namespace dometer::dns::message {
    TEST(BuilderTest, BuildsAMessage) {
        auto build_result = builder::new_builder().build();
        ASSERT_TRUE(build_result) << build_result.error().message;
    }

    TEST(BuilderTest, CanSetHeaderValues) {
        auto build_result = builder::new_builder()
            .set_id(54321)
            .set_qr(dns::qr::reply)
            .set_rcode(dns::rcode::nxdomain)
            .build();

        ASSERT_TRUE(build_result) << build_result.error().message;
        ASSERT_EQ(build_result->get_id(), 54321);
        ASSERT_EQ(build_result->get_qr(), dns::qr::reply);
        ASSERT_EQ(build_result->get_rcode(), dns::rcode::nxdomain);
    }

    TEST(BuilderTest, CanAddARecord) {
        auto build_result = builder::new_builder()
            .set_id(54321)
            .set_qr(dns::qr::reply)
            .set_rcode(dns::rcode::noerror)
            .add_answer(dns::record{
                "google.com",
                dns::type::a,
                dns::class_::in,
                300,
                "50.60.70.80"
            })
            .build();

        ASSERT_TRUE(build_result) << build_result.error().message;
        ASSERT_EQ(build_result->get_an_count(), 1);

        auto answers_result = build_result->get_answers();
        ASSERT_TRUE(answers_result) << answers_result.error().message;
        ASSERT_EQ(answers_result->size(), 1);

        auto answer = answers_result->at(0);
        ASSERT_EQ(answer.name, "google.com");
        ASSERT_EQ(answer.type, dns::type::a);
        ASSERT_EQ(answer.class_, dns::class_::in);
        ASSERT_EQ(answer.ttl, 300);
        ASSERT_EQ(answer.rdata, "50.60.70.80");
    }
}