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
#include "dometer/dns/handler/error.hpp"
#include "dometer/dns/handler/resolving_handler.hpp"
#include "dometer/event/callback.hpp"
#include "dometer/event/emitter.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::handler {
    resolving_handler::resolving_handler(
        std::shared_ptr<dometer::event::emitter<dometer::dns::event::any_event>> emitter,
        std::shared_ptr<dns::resolver::resolver> resolver
    ) : resolving_handler(std::chrono::steady_clock(), emitter, resolver) {}

    resolving_handler::resolving_handler(
                std::chrono::steady_clock clock,
                std::shared_ptr<dometer::event::emitter<dns::event::any_event>> emitter,
                std::shared_ptr<dns::resolver::resolver> resolver)
        :   clock(clock),
            emitter(emitter),
            resolver(resolver)
    {}

    std::x::expected<std::vector<uint8_t>, error> resolving_handler::handle(
        uint64_t session_id, std::vector<uint8_t> query_bytes
    ) {
        auto query = parse_query(session_id, query_bytes);
        auto reply = handle(session_id, query);

        if(query && reply) {
            reply->set_id(query->get_id());
        }

        if(!reply) {
            return std::x::unexpected<error>(reply.error());
        }

        const uint8_t* reply_ptr = *reply;
        return std::vector<uint8_t>(reply_ptr, reply_ptr + reply->size());
    }

    std::x::expected<dns::message::message, error> resolving_handler::handle(
        uint64_t session_id,
        std::x::expected<dns::message::message, util::error> &query
    ) {
        if(!query) {
            return std::x::unexpected<error>(error(
                "The query is not valid.",
                error_code::invalid_query,
                query.error())
            );
        }

        if(query->get_opcode() != dns::opcode::query) {
            return dns::message::message_factory::not_implemented(*query);
        }

        return handle(session_id, *query);
    }

    std::x::expected<dns::message::message, error> resolving_handler::handle(
        uint64_t session_id, dns::message::message& query
    ) {
        auto question = query.get_question();
        if(!question) {
            return dns::message::message_factory::format_error(query);
        }

        return handle(session_id, *question);
    }

    std::x::expected<dns::message::message, error> resolving_handler::handle(
        uint64_t session_id, dometer::dns::question question
    ) {
        auto resolution = resolve_query(session_id, question);

        if(!resolution) {
            return std::x::unexpected<error>(error(
                "Failed to resolve query.",
                error_code::resolver_failure,
                resolution.error()
            ));
        }

        auto reply = parse_reply(session_id, *resolution);
        if(!reply) {
            return std::x::unexpected<error>(error(
                "The reply is not valid.",
                error_code::invalid_reply,
                reply.error()
            ));
        }

        return *reply;
    }

    std::x::expected<dometer::dns::message::message, util::error> resolving_handler::parse_query(
        uint64_t session_id, std::vector<uint8_t> bytes
    ) {
        auto query = dometer::dns::message::parser::parse(bytes);
        emitter->emit(dometer::dns::event::parse_query_event(session_id, query));
        return query;
    }

    std::x::expected<dometer::dns::message::message, util::error> resolving_handler::parse_reply(
        uint64_t session_id, std::vector<uint8_t> bytes
    ) {
        auto reply = dometer::dns::message::parser::parse(bytes);
        emitter->emit(dometer::dns::event::parse_reply_event(session_id, reply));
        return reply;
    }

    std::x::expected<std::vector<uint8_t>, util::error> resolving_handler::resolve_query(
        uint64_t session_id, dometer::dns::question& question
    ) {
        auto start = clock.now();
        auto resolution = resolver->resolve(question.qname, question.qclass, question.qtype);
        auto end = clock.now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        emitter->emit(dometer::dns::event::resolve_query_event(
            session_id, question, resolution, duration
        ));

        return resolution;
    }
}
