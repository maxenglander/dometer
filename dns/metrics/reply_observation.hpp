#pragma once

#include <string>
#include <tuple>

#include "metrics/observation.hpp"

namespace Dometer::Dns::Metrics {
    class ReplyObservationBuilder : public Dometer::Metrics::ObservationBuilder<std::string, std::string, std::string, bool> {
        public:
            Dometer::Metrics::Observation<std::string, std::string, std::string, bool> build() const;
            ReplyObservationBuilder& qclass(std::string);
            ReplyObservationBuilder& qname(std::string);
            ReplyObservationBuilder& qtype(std::string);
            ReplyObservationBuilder& valid(bool);
        private:
            std::string _qclass;
            std::string _qname;
            std::string _qtype;
            bool _valid;
    };

    struct ReplyObservation : Dometer::Metrics::Observation<std::string, std::string, std::string, bool> {
        ReplyObservation(std::tuple<std::string, std::string, std::string, bool>, uint64_t);
        static ReplyObservationBuilder newBuilder();
        using Builder = ReplyObservationBuilder;
    };
}
