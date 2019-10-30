#include <string>
#include <tuple>

#include "dns/metrics/reply_counter.hpp"
#include "dns/metrics/reply_observation.hpp"
#include "metrics/observation.hpp"

namespace Dometer::Dns::Metrics {
    ReplyObservation::ReplyObservation(uint64_t value,
                    std::tuple<std::string, std::string, std::string, bool> labelValues)
            :   Dometer::Metrics::Observation<uint64_t, std::string, std::string, std::string, bool>::Observation(
                    ReplyCounter::INSTANCE, value, labelValues
                )
    {}

    ReplyObservationBuilder ReplyObservation::newBuilder() {
        return ReplyObservationBuilder();
    }

    Dometer::Metrics::Observation<uint64_t, std::string, std::string, std::string, bool> ReplyObservationBuilder::build() const {
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