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
    TEST(ResolvWrapperConfTest, SetsEnvVarAndCreatesConfFile) {
        ASSERT_EQ(getenv("RESOLV_WRAPPER_CONF"), nullptr);

        auto wrapper = builder::new_conf_builder().build();
        ASSERT_EQ(wrapper.mode(), wrap_mode::conf);

        auto fname = wrapper.file_name();
        struct stat buffer;
        ASSERT_EQ(stat(fname.c_str(), &buffer), 0);
        ASSERT_STREQ(getenv("RESOLV_WRAPPER_CONF"), fname.c_str());
    }

    TEST(ResolvWrapperConfTest, PopulatesFileWithRecords) {
         auto wrapper = builder::new_conf_builder()
             .add_nameserver("127.0.0.53")
             .build();

        std::fstream fstream(wrapper.file_name());
        std::string line;

        getline(fstream, line);
        ASSERT_EQ(line, "nameserver 127.0.0.53");
    }

    TEST(ResolvWrapperConfTest, UnsetsEnvVarAndDeletesFile) {
        std::string fname;
        {
            auto wrapper = builder::new_conf_builder().build();
            fname = wrapper.file_name();
        }

        struct stat buffer;
        ASSERT_NE(stat(fname.c_str(), &buffer), 0);
        ASSERT_EQ(getenv("RESOLV_WRAPPER_CONF"), nullptr);
    }

    TEST(ResolvWrapperConfTest, FailsWithInvalidNameserver) {
         auto wrapper = builder::new_conf_builder()
             .add_nameserver("127.0.0.53")
             .build();

         ASSERT_EQ(res_init(), 0);

         unsigned char answer[PACKETSZ];
         int msglen = res_query("hello.world", ns_c_in, ns_t_a, answer, PACKETSZ);
         ASSERT_EQ(msglen, -1);
    }
}
