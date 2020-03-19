#include <functional>
#include <iostream>
#include <memory>
#include <stdlib.h>

#include "dometer/dns/class.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/message/builder.hpp"
#include "dometer/dns/message/message_factory.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/dns/handler/error.hpp"
#include "dometer/dns/handler/error_code.hpp"
#include "dometer/dns/handler/mock_handler.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/resolver/error_code.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/libresolv_helper.hpp"
#include "dometer/dns/resolver/libresolv_resolver.hpp"
#include "dometer/dns/server/server.hpp"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SaveArg;

namespace util = dometer::util;

namespace dometer::dns::resolver {
    class LibresolvResolverTest : public ::testing::Test {
        public:
            LibresolvResolverTest()
                : _handler(std::make_shared<dometer::dns::handler::mock_handler>()),
                  _server(std::static_pointer_cast<dometer::dns::handler::handler>(_handler))
            {}

            struct __res_state MakeResState() {
                struct __res_state stat;

                res_ninit(&stat);

                struct in_addr addr;
                inet_pton(AF_INET, "127.0.0.1", &addr);

                // Normalize options as much as possible.
                stat.options = 0;
                stat.ndots = 1;
                stat.nscount = 1;
                stat.nsaddr_list[0] = (struct sockaddr_in) {
                    .sin_family = AF_INET,
                    .sin_port = htons(6353),
                    .sin_addr = addr,
                };
                stat.retry = 1;

                return stat;
            }

            void SetUp() override {
                _server.start("127.0.0.1", 6353);
            }

            void TearDown() override {
                _server.stop();
            }
        protected:
            std::shared_ptr<dometer::dns::handler::mock_handler> _handler;
            dometer::dns::server::server _server;
    };

    TEST_F(LibresolvResolverTest, SendsQueryToNameserver) {
        libresolv_resolver resolver(libresolv_function::query,
                                    libresolv_helper::make_res_state_for_nameserver("127.0.0.1", 6353));

        std::vector<uint8_t> request_bytes(4096, 0);
        EXPECT_CALL(*_handler, handle)
            .WillOnce(DoAll(SaveArg<1>(&request_bytes), Return(std::vector<uint8_t>())));
        resolver.resolve("hello.world", class_::in, type::a);

        auto parse_result = dometer::dns::message::parser::parse(request_bytes);
        EXPECT_TRUE(parse_result) << parse_result.error().message;
        EXPECT_EQ(parse_result->get_qd_count(), 1);

        auto question_result = parse_result->get_question();
        EXPECT_TRUE(question_result) << question_result.error().message;
        EXPECT_EQ(question_result->qname, "hello.world");
        EXPECT_EQ(question_result->qclass, class_::in);
        EXPECT_EQ(question_result->qtype, type::a);
    }

    TEST_F(LibresolvResolverTest, ReturnsReplyFromNameserver) {
        libresolv_resolver resolver(libresolv_function::query, MakeResState());

        EXPECT_CALL(*_handler, handle).WillOnce(Invoke(&dometer::dns::handler::mock_handler::return_nxdomain));
        auto resolve_result = resolver.resolve("hello.world", class_::in, type::a);
        EXPECT_TRUE(resolve_result) << resolve_result.error().message;

        auto reply_bytes = *resolve_result;
        auto parse_result = dometer::dns::message::parser::parse(reply_bytes);
        EXPECT_TRUE(parse_result);

        auto reply = *parse_result;
        EXPECT_EQ(reply.get_rcode(), dometer::dns::rcode::nxdomain);
    }
}
