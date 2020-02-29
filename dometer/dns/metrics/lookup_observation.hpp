#pragma once

#include <string>
#include <tuple>

#include "dometer/dns/class.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/metrics/observation.hpp"

namespace dometer::dns::metrics {
    class LookupObservationBuilder
            :    public dometer::metrics::ObservationBuilder<
                            /* duration */double,
                            /* qclass   */dometer::dns::Class,
                            /* qname    */std::string,
                            /* qtype    */dometer::dns::Type,
                            /* rcode    */std::string
                        > {
        public:
            dometer::metrics::Observation<
                            /* duration */double,
                            /* qclass   */dometer::dns::Class,
                            /* qname    */std::string,
                            /* qtype    */dometer::dns::Type,
                            /* rcode    */std::string
                        > build() const;
            LookupObservationBuilder& duration(double duration);
            LookupObservationBuilder& rcode(std::string);
            LookupObservationBuilder& qclass(dometer::dns::Class);
            LookupObservationBuilder& qname(std::string);
            LookupObservationBuilder& qtype(dometer::dns::Type);
        private:
            double _duration;
            std::string _rcode;
            dometer::dns::Class _qclass = dometer::dns::Class::IN;
            std::string _qname;
            dometer::dns::Type _qtype = dometer::dns::Type::A;
    };

    struct LookupObservation : dometer::metrics::Observation<
                                   /* duration */double,
                                   /* qclass   */dometer::dns::Class,
                                   /* qname    */std::string,
                                   /* qtype    */dometer::dns::Type,
                                   /* rcode    */std::string
                               > {
        LookupObservation(double, std::tuple<dometer::dns::Class, std::string, dometer::dns::Type, std::string>);
        static LookupObservationBuilder newBuilder();
        using Builder = LookupObservationBuilder;
    };
}
