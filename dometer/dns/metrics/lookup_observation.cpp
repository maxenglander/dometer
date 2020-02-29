#include <string>
#include <tuple>

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/metrics/lookup_observation.hpp"
#include "dometer/dns/metrics/lookup_summary.hpp"
#include "dometer/dns/metrics/type_label.hpp"
#include "dometer/metrics/observation.hpp"

namespace dometer::dns::metrics {
    LookupObservation::LookupObservation(double duration,
                std::tuple<
                    /* qclass */dometer::dns::Class,
                    /* qname  */std::string,
                    /* qtype  */dometer::dns::Type,
                    /* rcode  */std::string
                > labelValues)
            :   dometer::metrics::Observation<
                    /* duration */double,
                    /* qclass */dometer::dns::Class,
                    /* qname  */std::string,
                    /* qtype  */dometer::dns::Type,
                    /* rcode  */std::string
                >::Observation(
                    duration, labelValues
                )
    {}

    LookupObservationBuilder LookupObservation::newBuilder() {
        return LookupObservationBuilder();
    }

    dometer::metrics::Observation<double,
                                  dometer::dns::Class,
                                  std::string,
                                  dometer::dns::Type,
                                  std::string> LookupObservationBuilder::build() const {
        return LookupObservation(_duration, std::make_tuple(_qclass, _qname, _qtype, _rcode));
    }

    LookupObservationBuilder& LookupObservationBuilder::duration(double seconds) {
        this->_duration = seconds;
        return *this;
    }

    LookupObservationBuilder& LookupObservationBuilder::rcode(std::string rcode) {
        this->_rcode = rcode;
        return *this;
    }

    LookupObservationBuilder& LookupObservationBuilder::qclass(dometer::dns::Class qclass) {
        this->_qclass = qclass;
        return *this;
    }

    LookupObservationBuilder& LookupObservationBuilder::qname(std::string qname) {
        this->_qname = qname;
        return *this;
    }

    LookupObservationBuilder& LookupObservationBuilder::qtype(dometer::dns::Type qtype) {
        this->_qtype = qtype;
        return *this;
    }
}
