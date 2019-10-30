#pragma once

#include <string>
#include <tuple>

#include "dns/type.hpp"
#include "metrics/observation.hpp"

namespace Dometer::Dns::Metrics {
    class QueryObservationBuilder
            :    public Dometer::Metrics::ObservationBuilder<uint64_t, std::string, std::string, Dometer::Dns::Type, bool> {
        public:
            Dometer::Metrics::Observation<uint64_t, std::string, std::string, Dometer::Dns::Type, bool> build() const;
            QueryObservationBuilder& qclass(std::string);
            QueryObservationBuilder& qname(std::string);
            QueryObservationBuilder& qtype(Dometer::Dns::Type);
            QueryObservationBuilder& valid(bool);
        private:
            std::string _qclass;
            std::string _qname;
            Dometer::Dns::Type _qtype = Dometer::Dns::Type::A;
            bool _valid;
    };

    struct QueryObservation : Dometer::Metrics::Observation<uint64_t, std::string, std::string, Dometer::Dns::Type, bool> {
        QueryObservation(uint64_t, std::tuple<std::string, std::string, Dometer::Dns::Type, bool>);
        static QueryObservationBuilder newBuilder();
        using Builder = QueryObservationBuilder;
    };
}
