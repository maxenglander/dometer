#include <arpa/nameser.h>
#include <exception>
#include <iostream>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <utility>
#include <vector>

#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"
#include "std/x/unique.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    std::x::expected<Message, util::Error> Parser::parse(std::vector<uint8_t> bytes) {
        return parse(bytes.data(), bytes.size());
    }

    std::x::expected<Message, util::Error> Parser::parse(uint8_t *bytePtr, size_t size) {
        std::unique_ptr<uint8_t[]> bytes(new uint8_t[size]);
        std::copy(bytePtr, bytePtr + size, bytes.get());
        return parse(std::move(bytes), size);
    }

    std::x::expected<Message, util::Error> Parser::parse(std::unique_ptr<uint8_t[]> bytes, size_t size) {
        ns_msg handle;

        if(size < 0 || size > PACKETSZ) {
            return std::x::unexpected<util::Error>(util::Error(
                "Invalid message length.",
                std::vector<std::string>({
                    "Min length: 0",
                    "Max length: " + std::to_string(PACKETSZ),
                    "Length: " + std::to_string(size)
                })
            ));
        }

        if(ns_initparse(bytes.get(), size, &handle) < 0) {
            return std::x::unexpected<util::Error>(util::Error(
                "Failed to parse bytes into DNS message.",
                util::Error(
                    std::string(strerror(errno)),
                    errno
                )
            ));
        }

        return Message(std::move(bytes), handle, size);
    }
}