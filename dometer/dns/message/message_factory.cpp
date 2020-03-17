#include <arpa/nameser.h>
#include <exception>
#include <iostream>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <utility>

#include "dometer/dns/class.hpp"
#include "dometer/dns/opcode.hpp"
#include "dometer/dns/qr.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/message_factory.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"
#include "std/x/unique.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    message message_factory::copy_message(const message& message) {
        std::unique_ptr<uint8_t[]> bytes(new uint8_t[message.size()]);
        uint8_t *byte_ptr = message;
        size_t size = message.size();
        std::copy(byte_ptr, byte_ptr + size, bytes.get());
        return *parser::parse(std::move(bytes), message.size());
    }

    message message_factory::format_error(const message& message) {
        auto reply = copy_message(message);
        reply.set_qr(qr::reply);
        reply.set_rcode(rcode::formerr);
        return reply;
    }

    message message_factory::not_implemented(const message& query) {
        auto reply = copy_message(query);;
        reply.set_qr(qr::reply);
        reply.set_rcode(rcode::notimpl);
        return reply;
    }

    message message_factory::nxdomain(const message& query) {
        auto reply = copy_message(query);;
        reply.set_qr(qr::reply);
        reply.set_rcode(rcode::nxdomain);
        return reply;
    }

    message message_factory::server_failure(const message& query) {
        auto reply = copy_message(query);
        reply.set_qr(qr::reply);
        reply.set_rcode(rcode::servfail);
        return reply;
    }
}
