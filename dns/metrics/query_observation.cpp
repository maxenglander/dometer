#include <string>
#include <tuple>

#include "dns/type.hpp"
#include "dns/metrics/query_counter.hpp"
#include "dns/metrics/query_observation.hpp"
#include "dns/metrics/type_label.hpp"
#include "metrics/observation.hpp"

namespace Dometer::Dns::Metrics {
    QueryObservation::QueryObservation(
                std::tuple<std::string, std::string, Dometer::Dns::Type, bool> labelValues, uint64_t value)
            :   Dometer::Metrics::Observation<std::string, std::string, Dometer::Dns::Type, bool>::Observation(
                    QueryCounter::INSTANCE, labelValues, value
                )
    {}

    QueryObservationBuilder QueryObservation::newBuilder() {
        return QueryObservationBuilder();
    }

    Dometer::Metrics::Observation<std::string, std::string, Dometer::Dns::Type, bool> QueryObservationBuilder::build() const {
        return QueryObservation(std::make_tuple(_qclass, _qname, _qtype, _valid), 1);
    }

    QueryObservationBuilder& QueryObservationBuilder::qclass(std::string qclass) {
        this->_qclass = qclass;
        return *this;
    }

    QueryObservationBuilder& QueryObservationBuilder::qname(std::string qname) {
        this->_qname = qname;
        return *this;
    }

    QueryObservationBuilder& QueryObservationBuilder::qtype(Dometer::Dns::Type qtype) {
        this->_qtype = qtype;
        return *this;
    }

    QueryObservationBuilder& QueryObservationBuilder::valid(bool valid) {
        this->_valid = valid;
        return *this;
    }
}
