#include <string>
#include <tuple>

#include "dometer/dns/type.hpp"
#include "dometer/dns/metrics/lookup_observation.hpp"
#include "dometer/dns/metrics/lookup_summary.hpp"
#include "dometer/dns/metrics/type_label.hpp"
#include "dometer/metrics/observation.hpp"

namespace dometer::dns::metrics {
    LookupObservation::LookupObservation(double duration,
                std::tuple<std::string, std::string, dometer::dns::Type> labelValues)
            :   dometer::metrics::Observation<double, std::string, std::string, dometer::dns::Type>::Observation(
                    duration, labelValues
                )
    {}

    LookupObservationBuilder LookupObservation::newBuilder() {
        return LookupObservationBuilder();
    }

    dometer::metrics::Observation<double, std::string, std::string, dometer::dns::Type> LookupObservationBuilder::build() const {
        return LookupObservation(_duration, std::make_tuple(_qclass, _qname, _qtype));
    }

    LookupObservationBuilder& LookupObservationBuilder::duration(double seconds) {
        this->_duration = seconds;
        return *this;
    }

    LookupObservationBuilder& LookupObservationBuilder::qclass(std::string qclass) {
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
