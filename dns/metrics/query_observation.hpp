#pragma once

#include <string>
#include <tuple>

#include "dns/type.hpp"
#include "metrics/observation.hpp"

namespace dometer::dns::metrics {
    class QueryObservationBuilder
            :    public dometer::metrics::ObservationBuilder<uint64_t, std::string, std::string, dometer::dns::Type, bool> {
        public:
            dometer::metrics::Observation<uint64_t, std::string, std::string, dometer::dns::Type, bool> build() const;
            QueryObservationBuilder& qclass(std::string);
            QueryObservationBuilder& qname(std::string);
            QueryObservationBuilder& qtype(dometer::dns::Type);
            QueryObservationBuilder& valid(bool);
        private:
            std::string _qclass;
            std::string _qname;
            dometer::dns::Type _qtype = dometer::dns::Type::A;
            bool _valid;
    };

    struct QueryObservation : dometer::metrics::Observation<uint64_t, std::string, std::string, dometer::dns::Type, bool> {
        QueryObservation(uint64_t, std::tuple<std::string, std::string, dometer::dns::Type, bool>);
        static QueryObservationBuilder newBuilder();
        using Builder = QueryObservationBuilder;
    };
}
