#pragma once

#include <string>
#include <tuple>

#include "dometer/metrics/observation.hpp"

namespace dometer::dns::metrics {
    class ReplyObservationBuilder
            :    public dometer::metrics::ObservationBuilder<uint64_t, std::string, std::string, std::string, std::string, bool> {
        public:
            dometer::metrics::Observation<uint64_t, std::string, std::string, std::string, std::string, bool> build() const;
            ReplyObservationBuilder& qclass(std::string);
            ReplyObservationBuilder& qname(std::string);
            ReplyObservationBuilder& qtype(std::string);
            ReplyObservationBuilder& rcode(std::string);
            ReplyObservationBuilder& valid(bool);
        private:
            std::string _qclass;
            std::string _qname;
            std::string _qtype;
            std::string _rcode;
            bool _valid;
    };

    struct ReplyObservation : dometer::metrics::Observation<uint64_t, std::string, std::string, std::string, std::string, bool> {
        ReplyObservation(uint64_t, std::tuple<std::string, std::string, std::string, std::string, bool>);
        static ReplyObservationBuilder newBuilder();
        using Builder = ReplyObservationBuilder;
    };
}
