#include <string>
#include <tuple>

#include "metrics/descriptors.hpp"
#include "metrics/observation.hpp"
#include "metrics/query_observation.hpp"

namespace Dometer::Metrics {
    QueryObservation::QueryObservation(std::tuple<std::string, bool> labelValues, uint64_t value)
            : Observation<std::string, bool>::Observation(Descriptors::QUERY, labelValues, value) {}

    QueryObservationBuilder QueryObservation::newBuilder() {
        return QueryObservationBuilder();
    }

    Observation<std::string, bool> QueryObservationBuilder::build() const {
        return QueryObservation(std::make_tuple(_qname, _valid), 1);
    }

    QueryObservationBuilder& QueryObservationBuilder::qname(std::string qname) {
        this->_qname = qname;
        return *this;
    }

    QueryObservationBuilder& QueryObservationBuilder::valid(bool valid) {
        this->_valid = valid;
        return *this;
    }
}
