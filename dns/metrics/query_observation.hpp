#pragma once

#include <string>
#include <tuple>

#include "dns/type.hpp"
#include "metrics/observation.hpp"

namespace Dometer::Dns::Metrics {
    class QueryObservationBuilder
            :    public Dometer::Metrics::ObservationBuilder<std::string, std::string, Dometer::Dns::Type, bool> {
        public:
            Dometer::Metrics::Observation<std::string, std::string, Dometer::Dns::Type, bool> build() const;
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

    struct QueryObservation : Dometer::Metrics::Observation<std::string, std::string, Dometer::Dns::Type, bool> {
        QueryObservation(std::tuple<std::string, std::string, Dometer::Dns::Type, bool>, uint64_t);
        static QueryObservationBuilder newBuilder();
        using Builder = QueryObservationBuilder;
    };
}
