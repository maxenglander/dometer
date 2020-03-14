#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <resolv.h>
#include <sys/stat.h>

#include "cwrap/resolv_wrapper/builder.hpp"
#include "cwrap/resolv_wrapper/resolv_wrapper.hpp"
#include "cwrap/resolv_wrapper/wrap_mode.hpp"
#include "gtest/gtest.h"

namespace cwrap::resolv_wrapper {
    TEST(ResolvWrapperHostsTest, SetsEnvVarAndCreatesFileWithHosts) {
        ASSERT_EQ(getenv("RESOLV_WRAPPER_HOSTS"), nullptr);

        auto wrapper = builder::new_hosts_builder().build();
        ASSERT_EQ(wrapper.mode(), wrap_mode::hosts);

        auto fname = wrapper.file_name();
        struct stat buffer;
        ASSERT_EQ(stat(fname.c_str(), &buffer), 0);
        ASSERT_STREQ(getenv("RESOLV_WRAPPER_HOSTS"), fname.c_str());
    }

    TEST(ResolvWrapperHostsTest, PopulatesFileWithRecords) {
         auto wrapper = builder::new_hosts_builder()
             .add_a_record("hello.world", "1.2.3.4")
             .add_a_record("goodbye.world", "4.3.2.1")
             .build();

        std::fstream fstream(wrapper.file_name());
        std::string line;

        getline(fstream, line);
        ASSERT_EQ(line, "A hello.world 1.2.3.4");

        getline(fstream, line);
        ASSERT_EQ(line, "A goodbye.world 4.3.2.1");
    }

    TEST(ResolvWrapperHostsTest, UnsetsEnvVarAndDeletesFile) {
        std::string fname;
        {
            auto wrapper = builder::new_hosts_builder().build();
            fname = wrapper.file_name();
        }

        struct stat buffer;
        ASSERT_NE(stat(fname.c_str(), &buffer), 0);
        ASSERT_EQ(getenv("RESOLV_WRAPPER_HOSTS"), nullptr);
    }

    TEST(ResolvWrapperHostsTest, AnswersQueryWithNoerror) {
         auto wrapper = builder::new_hosts_builder()
             .add_a_record("hello.world", "1.2.3.4")
             .build();

         ASSERT_EQ(res_init(), 0);

         unsigned char answer[PACKETSZ];
         int msglen = res_query("hello.world", ns_c_in, ns_t_a, answer, PACKETSZ);
         ASSERT_GT(msglen, 0);

         ns_msg handle;
         ASSERT_EQ(ns_initparse(answer, msglen, &handle), 0);
         ASSERT_EQ(ns_msg_count(handle, ns_s_an), 1);

         ns_rr rr;
         ASSERT_EQ(ns_parserr(&handle, ns_s_an, 0, &rr), 0);
         ASSERT_EQ(ns_rr_type(rr), ns_t_a);
         ASSERT_STREQ(inet_ntoa(*(struct in_addr*)ns_rr_rdata(rr)), "1.2.3.4");
    }
}
