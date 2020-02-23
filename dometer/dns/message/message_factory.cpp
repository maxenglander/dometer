#include <arpa/nameser.h>
#include <exception>
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
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"
#include "std/x/unique.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    Message MessageFactory::copyMessage(const Message& message) {
        std::unique_ptr<uint8_t[]> bytes(new uint8_t[message.size()]);
        uint8_t *bytePtr = message;
        size_t size = message.size();
        std::copy(bytePtr, bytePtr + size, bytes.get());
        return *makeMessage(std::move(bytes), message.size());
    }

    Message MessageFactory::formatError(const Message& message) {
        auto reply = copyMessage(message);
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::FORMERR);
        return reply;
    }

    std::x::expected<Message, util::Error> MessageFactory::makeMessage(uint8_t *bytePtr, size_t size) {
        std::unique_ptr<uint8_t[]> bytes(new uint8_t[size]);
        std::copy(bytePtr, bytePtr + size, bytes.get());
        return makeMessage(std::move(bytes), size);
    }

    std::x::expected<Message, util::Error> MessageFactory::makeMessage(std::unique_ptr<uint8_t[]> bytes, size_t size) {
        try {
            return Message(std::move(bytes), size);
        } catch(std::runtime_error& e) {
            return std::x::unexpected<util::Error>(util::Error{e.what(), 0});
        }
    }

    Message MessageFactory::notImplemented(const Message& query) {
        auto reply = copyMessage(query);;
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::NOTIMP);
        return reply;
    }

    Message MessageFactory::serverFailure(const Message& query) {
        auto reply = copyMessage(query);
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::SERVFAIL);
        return reply;
    }
}
