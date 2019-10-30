#pragma once

#include <string>
#include <tuple>

#include "dns/type.hpp"
#include "metrics/observation.hpp"

namespace Dometer::Dns::Metrics {
    class LookupObservationBuilder
            :    public Dometer::Metrics::ObservationBuilder<double, std::string, std::string, Dometer::Dns::Type> {
        public:
            Dometer::Metrics::Observation<double, std::string, std::string, Dometer::Dns::Type> build() const;
            LookupObservationBuilder& duration(double durationMicroseconds);
            LookupObservationBuilder& qclass(std::string);
            LookupObservationBuilder& qname(std::string);
            LookupObservationBuilder& qtype(Dometer::Dns::Type);
        private:
            uint64_t _durationMicroseconds;
            std::string _qclass;
            std::string _qname;
            Dometer::Dns::Type _qtype = Dometer::Dns::Type::A;
    };

    struct LookupObservation : Dometer::Metrics::Observation<double, std::string, std::string, Dometer::Dns::Type> {
        LookupObservation(double, std::tuple<std::string, std::string, Dometer::Dns::Type>);
        static LookupObservationBuilder newBuilder();
        using Builder = LookupObservationBuilder;
    };
}
