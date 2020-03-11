#include "gtest/gtest.h"
#include "cwrap/resolv_wrapper/builder.hpp"
#include "cwrap/resolv_wrapper/resolv_wrapper.hpp"

namespace cwrap::resolv_wrapper {
    TEST(ResolvWrapper, MakeResolvWrapper) {
        auto _wrapper = builder::new_hosts_builder().build();
        SUCCEED();
    }
}
