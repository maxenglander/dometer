#include <string>
#include <tuple>

#include "metrics/descriptors.hpp"
#include "metrics/observation.hpp"
#include "metrics/query_observation.hpp"

namespace Dometer::Metrics {
    QueryObservation::QueryObservation(std::tuple<std::string, std::string, std::string, bool> labelValues, uint64_t value)
            : Observation<std::string, std::string, std::string, bool>::Observation(Descriptors::QUERY, labelValues, value) {}

    QueryObservationBuilder QueryObservation::newBuilder() {
        return QueryObservationBuilder();
    }

    Observation<std::string, std::string, std::string, bool> QueryObservationBuilder::build() const {
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

    QueryObservationBuilder& QueryObservationBuilder::qtype(std::string qtype) {
        this->_qtype = qtype;
        return *this;
    }

    QueryObservationBuilder& QueryObservationBuilder::valid(bool valid) {
        this->_valid = valid;
        return *this;
    }
}
