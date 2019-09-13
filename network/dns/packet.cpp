#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <utility>

#include "experimental/expected.hpp"
#include "network/dns/class.hpp"
#include "network/dns/packet.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    Packet::Packet(Packet&& packet)
        :    header(packet.header),
             bytes(std::move(packet.bytes)),
             handle(std::exchange(packet.handle, {0})),
             size(packet.size)
    {}

    Packet::Packet(std::unique_ptr<uint8_t[]> bytes, ns_msg handle, size_t size)
        :    header(Header{
                 ns_msg_getflag(handle, ns_f_aa),
                 ns_msg_id(handle),
                 (uint8_t)ns_msg_getflag(handle, ns_f_opcode),
                 ns_msg_count(handle, ns_s_qd),
                 ns_msg_getflag(handle, ns_f_ra),
                 (uint8_t)ns_msg_getflag(handle, ns_f_rcode)
             }),
             bytes(std::move(bytes)),
             handle(handle),
             size(size)
    {}

    Packet::~Packet() {}

    expected<Packet, Error> Packet::makePacket(uint8_t *bytePtr, size_t size) {
        if(size < 0 || size > PACKETSZ)
            return unexpected<Error>(Error{"Invalid packet length: " + std::to_string(size), 0});

        auto bytes = std::make_unique<uint8_t[]>(size);
        std::copy(bytePtr, bytePtr + size, bytes.get());
        ns_msg handle;

        if(ns_initparse(bytes.get(), size, &handle) < 0)
            return unexpected<Error>(Error({strerror(errno), errno}));

        return Packet(std::move(bytes), handle, size);
    }

    expected<Question, Error> Packet::question() {
        if(header.qdcount != 1)
            return unexpected<Error>(Error{"qdcount is not equal to 1"});

        ns_rr question;

        if(ns_parserr(&handle, ns_s_qd, 0, &question) != 0)
            return unexpected<Error>(Error{strerror(errno), errno});

        return Question{
            std::string(ns_rr_name(question)),
            Type(ns_rr_type(question)),
            Class(ns_rr_class(question))
        };
    }
}
