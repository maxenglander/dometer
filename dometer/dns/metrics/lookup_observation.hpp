#pragma once

#include <string>
#include <tuple>

#include "dometer/dns/class.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/metrics/observation.hpp"

namespace dometer::dns::metrics {
    class lookup_observation_builder
            :    public dometer::metrics::observation_builder<
                     /* duration */double,
                     /* error    */std::string,
                     /* qclass   */dometer::dns::class_,
                     /* qname    */std::string,
                     /* qtype    */dometer::dns::type,
                     /* rcode    */std::string
                 > {
        public:
            dometer::metrics::observation<
                     /* duration */double,
                     /* error    */std::string,
                     /* qclass   */dometer::dns::class_,
                     /* qname    */std::string,
                     /* qtype    */dometer::dns::type,
                     /* rcode    */std::string
                 > build() const;
            lookup_observation_builder& duration(double duration);
            lookup_observation_builder& error(std::string);
            lookup_observation_builder& qclass(dometer::dns::class_);
            lookup_observation_builder& qname(std::string);
            lookup_observation_builder& qtype(dometer::dns::type);
            lookup_observation_builder& rcode(std::string);
        private:
            double _duration;
            std::string _error;
            std::string _rcode;
            dometer::dns::class_ _qclass = dometer::dns::class_::in;
            std::string _qname;
            dometer::dns::type _qtype = dometer::dns::type::a;
    };

    struct lookup_observation : dometer::metrics::observation<
                                   /* duration */double,
                                   /* error    */std::string,
                                   /* qclass   */dometer::dns::class_,
                                   /* qname    */std::string,
                                   /* qtype    */dometer::dns::type,
                                   /* rcode    */std::string
                               > {
        lookup_observation(double, std::tuple<std::string, dometer::dns::class_, std::string, dometer::dns::type, std::string>);
        static lookup_observation_builder new_builder();
        using Builder = lookup_observation_builder;
    };
}
