#include <algorithm>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <netdb.h>
#include <resolv.h>
#include <string>

#include "experimental/expected.hpp"
#include "network/dns/native_resolver.hpp"
#include "util/error.hpp"

using namespace std::experimental;

namespace Dometer::Network::Dns {
    expected<Packet, Error> NativeResolver::resolve(Packet packet) {
        return unexpected<Error>(Error{"Not yet implemented", 0});
    }
}
