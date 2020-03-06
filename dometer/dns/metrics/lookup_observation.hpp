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
                            /* error    */std::string,
                            /* qclass   */dometer::dns::dns_class,
                            /* qname    */std::string,
                            /* qtype    */dometer::dns::type,
                            /* rcode    */std::string
                        > {
        public:
            dometer::metrics::Observation<
                            /* duration */double,
                            /* error    */std::string,
                            /* qclass   */dometer::dns::dns_class,
                            /* qname    */std::string,
                            /* qtype    */dometer::dns::type,
                            /* rcode    */std::string
                        > build() const;
            LookupObservationBuilder& duration(double duration);
            LookupObservationBuilder& error(std::string);
            LookupObservationBuilder& rcode(std::string);
            LookupObservationBuilder& qclass(dometer::dns::dns_class);
            LookupObservationBuilder& qname(std::string);
            LookupObservationBuilder& qtype(dometer::dns::type);
        private:
            double _duration;
            std::string _error;
            std::string _rcode;
            dometer::dns::dns_class _qclass = dometer::dns::dns_class::IN;
            std::string _qname;
            dometer::dns::type _qtype = dometer::dns::type::A;
    };

    struct LookupObservation : dometer::metrics::Observation<
                                   /* duration */double,
                                   /* error    */std::string,
                                   /* qclass   */dometer::dns::dns_class,
                                   /* qname    */std::string,
                                   /* qtype    */dometer::dns::type,
                                   /* rcode    */std::string
                               > {
        LookupObservation(double, std::tuple<std::string, dometer::dns::dns_class, std::string, dometer::dns::type, std::string>);
        static LookupObservationBuilder newBuilder();
        using Builder = LookupObservationBuilder;
    };
}
