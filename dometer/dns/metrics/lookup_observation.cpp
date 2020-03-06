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
                    /* error  */std::string,
                    /* qclass */dometer::dns::class_,
                    /* qname  */std::string,
                    /* qtype  */dometer::dns::type,
                    /* rcode  */std::string
                > labelValues)
            :   dometer::metrics::Observation<
                    /* duration */double,
                    /* error  */std::string,
                    /* qclass */dometer::dns::class_,
                    /* qname  */std::string,
                    /* qtype  */dometer::dns::type,
                    /* rcode  */std::string
                >::Observation(
                    duration, labelValues
                )
    {}

    LookupObservationBuilder LookupObservation::newBuilder() {
        return LookupObservationBuilder();
    }

    dometer::metrics::Observation<double,
                                  std::string,
                                  dometer::dns::class_,
                                  std::string,
                                  dometer::dns::type,
                                  std::string> LookupObservationBuilder::build() const {
        return LookupObservation(_duration, std::make_tuple(_error, _qclass, _qname, _qtype, _rcode));
    }

    LookupObservationBuilder& LookupObservationBuilder::duration(double seconds) {
        this->_duration = seconds;
        return *this;
    }

    LookupObservationBuilder& LookupObservationBuilder::error(std::string error) {
        this->_error = error;
        return *this;
    }

    LookupObservationBuilder& LookupObservationBuilder::rcode(std::string rcode) {
        this->_rcode = rcode;
        return *this;
    }

    LookupObservationBuilder& LookupObservationBuilder::qclass(dometer::dns::class_ qclass) {
        this->_qclass = qclass;
        return *this;
    }

    LookupObservationBuilder& LookupObservationBuilder::qname(std::string qname) {
        this->_qname = qname;
        return *this;
    }

    LookupObservationBuilder& LookupObservationBuilder::qtype(dometer::dns::type qtype) {
        this->_qtype = qtype;
        return *this;
    }
}
