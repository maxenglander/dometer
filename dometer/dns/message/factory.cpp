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
#include "dometer/dns/message/factory.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"
#include "std/x/unique.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    Message Factory::copyMessage(const Message& message) {
        std::unique_ptr<uint8_t[]> bytes(new uint8_t[message.size()]);
        uint8_t *bytePtr = message;
        size_t size = message.size();
        std::copy(bytePtr, bytePtr + size, bytes.get());
        return *Parser::parse(std::move(bytes), message.size());
    }

    Message Factory::formatError(const Message& message) {
        auto reply = copyMessage(message);
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::FORMERR);
        return reply;
    }

    Message Factory::notImplemented(const Message& query) {
        auto reply = copyMessage(query);;
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::NOTIMPL);
        return reply;
    }

    Message Factory::serverFailure(const Message& query) {
        auto reply = copyMessage(query);
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::SERVFAIL);
        return reply;
    }
}
