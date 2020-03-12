#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <resolv.h>
#include <sys/stat.h>

#include "gtest/gtest.h"
#include "cwrap/resolv_wrapper/builder.hpp"
#include "cwrap/resolv_wrapper/resolv_wrapper.hpp"
#include "cwrap/resolv_wrapper/wrap_mode.hpp"

namespace cwrap::resolv_wrapper {
    TEST(hosts_resolv_wrapper, upon_build_sets_env_var_and_creates_file_with_hosts) {
        ASSERT_EQ(getenv("RESOLV_WRAPPER_HOSTS"), nullptr);

        auto wrapper = builder::new_hosts_builder().build();
        ASSERT_EQ(wrapper.mode(), wrap_mode::hosts);

        auto fname = wrapper.file_name();
        struct stat buffer;
        ASSERT_EQ(stat(fname.c_str(), &buffer), 0);
        ASSERT_STREQ(getenv("RESOLV_WRAPPER_HOSTS"), fname.c_str());
    }

    TEST(hosts_resolv_wrapper, upon_build_populates_file_with_records) {
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

    TEST(hosts_resolv_wrapper, upon_destruct_unsets_env_var_and_deletes_file) {
        std::string fname;
        {
            auto wrapper = builder::new_hosts_builder().build();
            fname = wrapper.file_name();
            ASSERT_EQ(wrapper.mode(), wrap_mode::hosts);
        }

        struct stat buffer;
        ASSERT_NE(stat(fname.c_str(), &buffer), 0);
        ASSERT_EQ(getenv("RESOLV_WRAPPER_HOSTS"), nullptr);
    }

    TEST(hosts_resolv_wrapper, upon_matching_query_answers_noerror) {
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
