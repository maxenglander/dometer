#include <string>
#include <tuple>

#include "dns/type.hpp"
#include "dns/metrics/lookup_observation.hpp"
#include "dns/metrics/lookup_summary.hpp"
#include "dns/metrics/type_label.hpp"
#include "metrics/observation.hpp"

namespace Dometer::Dns::Metrics {
    LookupObservation::LookupObservation(double durationMicroseconds,
                std::tuple<std::string, std::string, Dometer::Dns::Type> labelValues)
            :   Dometer::Metrics::Observation<double, std::string, std::string, Dometer::Dns::Type>::Observation(
                    LookupSummary::INSTANCE, durationMicroseconds, labelValues
                )
    {}

    LookupObservationBuilder LookupObservation::newBuilder() {
        return LookupObservationBuilder();
    }

    Dometer::Metrics::Observation<double, std::string, std::string, Dometer::Dns::Type> LookupObservationBuilder::build() const {
        return LookupObservation(_durationMicroseconds, std::make_tuple(_qclass, _qname, _qtype));
    }

    LookupObservationBuilder& LookupObservationBuilder::duration(double microseconds) {
        this->_durationMicroseconds = microseconds;
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

    LookupObservationBuilder& LookupObservationBuilder::qtype(Dometer::Dns::Type qtype) {
        this->_qtype = qtype;
        return *this;
    }
}
