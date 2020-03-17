#include <arpa/inet.h>
#include <functional>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <resolv.h>
#include <stdlib.h>

#include "dometer/dns/class.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/message/builder.hpp"
#include "dometer/dns/message/message_factory.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/dns/handler/mock_handler.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/libresolv_resolver.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/util/error.hpp"
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
                struct in_addr addr;
                inet_pton(AF_INET, "127.0.0.1", &addr);

                struct __res_state stat;
                stat.nscount = 1;
                stat.nsaddr_list[0] = (struct sockaddr_in) {
                    .sin_family = AF_INET,
                    .sin_port = htons(6353),
                    .sin_addr = addr,
                };
                stat.retry = 1;
                stat._u._ext.nscount = 0;
                stat._u._ext.nsaddrs[0] = NULL;

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

    std::x::expected<std::vector<uint8_t>, util::error> return_nxdomain(
        uint64_t session_id, std::vector<uint8_t> bytes
    ) {
        auto parse_result = dometer::dns::message::parser::parse(bytes);
        if(!parse_result) {
            return std::x::unexpected<util::error>(util::error{ "Failed to parse request bytes." });
        }

        auto reply = dometer::dns::message::message_factory::nxdomain(*parse_result);
        return std::vector<uint8_t>((uint8_t*)reply, (uint8_t*)reply + reply.size());
    }

    TEST_F(LibresolvResolverTest, SendsQueryToNameserver) {
        libresolv_resolver resolver(libresolv_function::query, MakeResState());

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

        EXPECT_CALL(*_handler, handle).WillOnce(Invoke(&return_nxdomain));
        auto resolve_result = resolver.resolve("hello.world", class_::in, type::a);
        EXPECT_TRUE(resolve_result) << resolve_result.error().message;

        auto reply_bytes = *resolve_result;
        auto parse_result = dometer::dns::message::parser::parse(reply_bytes);
        EXPECT_TRUE(parse_result);

        auto reply = *parse_result;
        EXPECT_EQ(reply.get_rcode(), dometer::dns::rcode::nxdomain);
    }
}
