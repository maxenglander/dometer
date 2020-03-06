#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/event/parse_query_event.hpp"
#include "dometer/dns/event/parse_reply_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/message_factory.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/dns/handler/resolving_handler.hpp"
#include "dometer/event/callback.hpp"
#include "dometer/event/emitter.hpp"
#include "dometer/util/error.hpp"
#include "dometer/util/human_error_encoder.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::handler {
    resolving_handler::resolving_handler(
        dometer::event::emitter<dometer::dns::event::any_event> emitter,
        std::shared_ptr<dns::resolver::Resolver> resolver
    ) : resolving_handler(std::chrono::steady_clock(), emitter, resolver) {}

    resolving_handler::resolving_handler(
                std::chrono::steady_clock clock,
                dometer::event::emitter<dns::event::any_event> emitter,
                std::shared_ptr<dns::resolver::Resolver> resolver)
        :   clock(clock),
            emitter(emitter),
            resolver(resolver)
    {}

    std::x::expected<std::vector<uint8_t>, util::error> resolving_handler::handle(
        uint64_t session_id, std::vector<uint8_t> queryBytes
    ) {
        auto query = parseQuery(session_id, queryBytes);
        auto reply = handle(session_id, query);

        if(query && reply) {
            reply->setId(query->getId());
        }

        if(!reply) {
            return std::x::unexpected<util::error>(reply.error());
        }

        const uint8_t* replyPtr = *reply;
        return std::vector<uint8_t>(replyPtr, replyPtr + reply->size());
    }

    std::x::expected<dns::message::message, util::error> resolving_handler::handle(
        uint64_t session_id,
        std::x::expected<dns::message::message, util::error> &query
    ) {
        if(!query) {
            return std::x::unexpected<util::error>(util::error("The query is not valid.", query.error()));
        }

        if(query->getOpCode() != dns::OpCode::QUERY) {
            return dns::message::MessageFactory::notImplemented(*query);
        }

        return handle(session_id, *query);
    }

    std::x::expected<dns::message::message, util::error> resolving_handler::handle(
        uint64_t session_id, dns::message::message& query
    ) {
        auto question = query.get_question();
        if(!question) {
            return dns::message::MessageFactory::formaterror(query);
        }

        return handle(session_id, *question);
    }

    std::x::expected<dns::message::message, util::error> resolving_handler::handle(
        uint64_t session_id, dometer::dns::question question
    ) {
        auto resolution = resolveQuery(session_id, question);

        if(!resolution) {
            return std::x::unexpected<dometer::util::error>(static_cast<dometer::util::error>(resolution.error()));
        }

        auto reply = parseReply(session_id, *resolution);
        if(!reply) {
            return std::x::unexpected<dometer::util::error>(reply.error());
        }

        return *reply;
    }

    std::x::expected<dometer::dns::message::message, util::error> resolving_handler::parseQuery(
        uint64_t session_id, std::vector<uint8_t> bytes
    ) {
        auto query = dometer::dns::message::parser::parse(bytes);
        emitter.emit(dometer::dns::event::parse_query_event(session_id, query));
        return query;
    }

    std::x::expected<dometer::dns::message::message, util::error> resolving_handler::parseReply(
        uint64_t session_id, std::vector<uint8_t> bytes
    ) {
        auto reply = dometer::dns::message::parser::parse(bytes);
        emitter.emit(dometer::dns::event::parse_reply_event(session_id, reply));
        return reply;
    }

    std::x::expected<std::vector<uint8_t>, util::error> resolving_handler::resolveQuery(
        uint64_t session_id, dometer::dns::question& question
    ) {
        auto start = clock.now();
        auto resolution = resolver->resolve(question.qname, question.qclass, question.qtype);
        auto end = clock.now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "resolve duration: " << duration.count() << std::endl;

        emitter.emit(dometer::dns::event::resolve_query_event(
            session_id, question, resolution, duration
        ));

        return resolution;
    }
}
