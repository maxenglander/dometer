#include <string>
#include <tuple>

#include "dometer/dns/type.hpp"
#include "dometer/dns/metrics/query_counter.hpp"
#include "dometer/dns/metrics/query_observation.hpp"
#include "dometer/dns/metrics/type_label.hpp"
#include "dometer/metrics/observation.hpp"

namespace dometer::dns::metrics {
    QueryObservation::QueryObservation(uint64_t value,
                    std::tuple<std::string, std::string, dometer::dns::Type, bool> labelValues)
            :   dometer::metrics::Observation<uint64_t, std::string, std::string, dometer::dns::Type, bool>::Observation(
                    value, labelValues
                )
    {}

    QueryObservationBuilder QueryObservation::newBuilder() {
        return QueryObservationBuilder();
    }

    dometer::metrics::Observation<uint64_t, std::string, std::string, dometer::dns::Type, bool> QueryObservationBuilder::build() const {
        return QueryObservation(1, std::make_tuple(_qclass, _qname, _qtype, _valid));
    }

    QueryObservationBuilder& QueryObservationBuilder::qclass(std::string qclass) {
        this->_qclass = qclass;
        return *this;
    }

    QueryObservationBuilder& QueryObservationBuilder::qname(std::string qname) {
        this->_qname = qname;
        return *this;
    }

    QueryObservationBuilder& QueryObservationBuilder::qtype(dometer::dns::Type qtype) {
        this->_qtype = qtype;
        return *this;
    }

    QueryObservationBuilder& QueryObservationBuilder::valid(bool valid) {
        this->_valid = valid;
        return *this;
    }
}
