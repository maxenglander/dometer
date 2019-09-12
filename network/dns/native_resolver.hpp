#pragma once

#include <arpa/nameser.h>
#include <string>
#include <vector>

#include "network/dns/response.hpp"
#include "std/experimental/expected.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    class NativeResolver {
        public:
            expected<Response, Error> lookup(std::string name, std::string type);
        private:
            expected<Response, Error> lookup(std::string name, ns_type type,
                    expected<Answer, Error> (*parser)(ns_msg* handle, ns_rr* rr));
            static expected<Answer, Error> parseARecord(ns_msg* handle, ns_rr* rr);
            static expected<Answer, Error> parseANYRecord(ns_msg* handle, ns_rr* rr);
            static expected<Answer, Error> parseSOARecord(ns_msg* handle, ns_rr* rr);
    };
}
