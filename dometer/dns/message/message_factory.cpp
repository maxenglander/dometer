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
    message MessageFactory::copyMessage(const message& message) {
        std::unique_ptr<uint8_t[]> bytes(new uint8_t[message.size()]);
        uint8_t *bytePtr = message;
        size_t size = message.size();
        std::copy(bytePtr, bytePtr + size, bytes.get());
        return *parser::parse(std::move(bytes), message.size());
    }

    message MessageFactory::formaterror(const message& message) {
        auto reply = copyMessage(message);
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::FORMERR);
        return reply;
    }

    message MessageFactory::notImplemented(const message& query) {
        auto reply = copyMessage(query);;
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::NOTIMPL);
        return reply;
    }

    message MessageFactory::serverFailure(const message& query) {
        auto reply = copyMessage(query);
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::SERVFAIL);
        return reply;
    }
}
