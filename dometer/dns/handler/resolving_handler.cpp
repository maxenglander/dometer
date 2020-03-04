#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/event/parse_query_event.hpp"
#include "dometer/dns/event/parse_reply_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/factory.hpp"
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
    ResolvingHandler::ResolvingHandler(
        dometer::event::Emitter<dometer::dns::event::AnyEvent> emitter,
        std::shared_ptr<dns::resolver::Resolver> resolver
    ) : ResolvingHandler(std::chrono::steady_clock(), emitter, resolver) {}

    ResolvingHandler::ResolvingHandler(
                std::chrono::steady_clock clock,
                dometer::event::Emitter<dns::event::AnyEvent> emitter,
                std::shared_ptr<dns::resolver::Resolver> resolver)
        :   clock(clock),
            emitter(emitter),
            resolver(resolver)
    {}

    std::x::expected<std::vector<uint8_t>, util::Error> ResolvingHandler::handle(
        uint64_t sessionId, std::vector<uint8_t> queryBytes
    ) {
        auto query = parseQuery(sessionId, queryBytes);
        auto reply = handle(sessionId, query);

        if(query && reply) {
            reply->setId(query->getId());
        }

        if(!reply) {
            return std::x::unexpected<util::Error>(reply.error());
        }

        const uint8_t* replyPtr = *reply;
        return std::vector<uint8_t>(replyPtr, replyPtr + reply->size());
    }

    std::x::expected<dns::message::Message, util::Error> ResolvingHandler::handle(
        uint64_t sessionId,
        std::x::expected<dns::message::Message, util::Error> &query
    ) {
        if(!query) {
            return std::x::unexpected<util::Error>(util::Error("The query is not valid.", query.error()));
        }

        if(query->getOpCode() != dns::OpCode::QUERY) {
            return dns::message::Factory::notImplemented(*query);
        }

        return handle(sessionId, *query);
    }

    std::x::expected<dns::message::Message, util::Error> ResolvingHandler::handle(
        uint64_t sessionId, dns::message::Message& query
    ) {
        auto question = query.getQuestion();
        if(!question) {
            return dns::message::Factory::formatError(query);
        }

        return handle(sessionId, *question);
    }

    std::x::expected<dns::message::Message, util::Error> ResolvingHandler::handle(
        uint64_t sessionId, dometer::dns::Question question
    ) {
        auto resolution = resolveQuery(sessionId, question);

        if(!resolution) {
            return std::x::unexpected<dometer::util::Error>(static_cast<dometer::util::Error>(resolution.error()));
        }

        auto reply = parseReply(sessionId, *resolution);
        if(!reply) {
            return std::x::unexpected<dometer::util::Error>(reply.error());
        }

        return *reply;
    }

    std::x::expected<dometer::dns::message::Message, util::Error> ResolvingHandler::parseQuery(
        uint64_t sessionId, std::vector<uint8_t> bytes
    ) {
        auto query = dometer::dns::message::Parser::parse(bytes);
        emitter.emit(dometer::dns::event::ParseQueryEvent(sessionId, query));
        return query;
    }

    std::x::expected<dometer::dns::message::Message, util::Error> ResolvingHandler::parseReply(
        uint64_t sessionId, std::vector<uint8_t> bytes
    ) {
        auto reply = dometer::dns::message::Parser::parse(bytes);
        emitter.emit(dometer::dns::event::ParseReplyEvent(sessionId, reply));
        return reply;
    }

    std::x::expected<std::vector<uint8_t>, util::Error> ResolvingHandler::resolveQuery(
        uint64_t sessionId, dometer::dns::Question& question
    ) {
        auto start = clock.now();
        auto resolution = resolver->resolve(question.qname, question.qclass, question.qtype);
        auto end = clock.now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        emitter.emit(dometer::dns::event::ResolveQueryEvent(
            sessionId, question, resolution, duration
        ));

        return resolution;
    }
}
