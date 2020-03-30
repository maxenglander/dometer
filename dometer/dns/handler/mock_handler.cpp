#include <memory>
#include <vector>

#include "gmock/gmock.h"
#include "dometer/dns/handler/error.hpp"
#include "dometer/dns/handler/error_code.hpp"
#include "dometer/dns/handler/mock_handler.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/message_factory.hpp"
#include "dometer/dns/message/parser.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::handler {
    std::x::expected<std::vector<uint8_t>, error> mock_handler::return_nxdomain(uint64_t, std::vector<uint8_t> bytes) {
        auto parse_result = dometer::dns::message::parser::parse(bytes);
        if(!parse_result) {
            return std::x::unexpected<error>(error(
                "Failed to parse request bytes.",
                error_code::invalid_query
            ));
        }

        auto reply = dometer::dns::message::message_factory::nxdomain(*parse_result);
        return std::vector<uint8_t>((uint8_t*)reply, (uint8_t*)reply + reply.size());
    }
}
