#include <string>
#include <tuple>

#include "dometer/dns/metrics/reply_counter.hpp"
#include "dometer/dns/metrics/reply_observation.hpp"
#include "dometer/metrics/observation.hpp"

namespace dometer::dns::metrics {
    ReplyObservation::ReplyObservation(uint64_t value,
                    std::tuple<std::string, std::string, std::string, bool> labelValues)
            :   dometer::metrics::Observation<uint64_t, std::string, std::string, std::string, bool>::Observation(
                    value, labelValues
                )
    {}

    ReplyObservationBuilder ReplyObservation::newBuilder() {
        return ReplyObservationBuilder();
    }

    dometer::metrics::Observation<uint64_t, std::string, std::string, std::string, bool> ReplyObservationBuilder::build() const {
        return ReplyObservation(1, std::make_tuple(_qclass, _qname, _qtype, _valid));
    }

    ReplyObservationBuilder& ReplyObservationBuilder::qclass(std::string qclass) {
        this->_qclass = qclass;
        return *this;
    }

    ReplyObservationBuilder& ReplyObservationBuilder::qname(std::string qname) {
        this->_qname = qname;
        return *this;
    }

    ReplyObservationBuilder& ReplyObservationBuilder::qtype(std::string qtype) {
        this->_qtype = qtype;
        return *this;
    }

    ReplyObservationBuilder& ReplyObservationBuilder::valid(bool valid) {
        this->_valid = valid;
        return *this;
    }

}
