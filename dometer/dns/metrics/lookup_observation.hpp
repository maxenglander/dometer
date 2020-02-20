#pragma once

#include <string>
#include <tuple>

#include "dometer/dns/type.hpp"
#include "dometer/metrics/observation.hpp"

namespace dometer::dns::metrics {
    class LookupObservationBuilder
            :    public dometer::metrics::ObservationBuilder<double, std::string, std::string, dometer::dns::Type> {
        public:
            dometer::metrics::Observation<double, std::string, std::string, dometer::dns::Type> build() const;
            LookupObservationBuilder& duration(double duration);
            LookupObservationBuilder& qclass(std::string);
            LookupObservationBuilder& qname(std::string);
            LookupObservationBuilder& qtype(dometer::dns::Type);
        private:
            double _duration;
            std::string _qclass;
            std::string _qname;
            dometer::dns::Type _qtype = dometer::dns::Type::A;
    };

    struct LookupObservation : dometer::metrics::Observation<double, std::string, std::string, dometer::dns::Type> {
        LookupObservation(double, std::tuple<std::string, std::string, dometer::dns::Type>);
        static LookupObservationBuilder newBuilder();
        using Builder = LookupObservationBuilder;
    };
}
