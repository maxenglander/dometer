#include "gtest/gtest.h"
#include "dometer/dns/util/resolv_wrapper.hpp"

namespace dometer::dns::util {
    TEST(ResolvWrapper, MakeResolvWrapper) {
        auto _wrapper1 = dometer::dns::util::resolv_wrapper::make_resolv_wrapper();
        SUCCEED();
    }
}
