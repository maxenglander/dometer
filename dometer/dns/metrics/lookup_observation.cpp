#include <string>
#include <tuple>

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/metrics/lookup_observation.hpp"
#include "dometer/dns/metrics/lookup_summary.hpp"
#include "dometer/dns/metrics/type_label.hpp"
#include "dometer/metrics/observation.hpp"

namespace dometer::dns::metrics {
    lookup_observation::lookup_observation(double duration,
                std::tuple<
                    /* error  */std::string,
                    /* qclass */dometer::dns::class_,
                    /* qname  */std::string,
                    /* qtype  */dometer::dns::type,
                    /* rcode  */std::string
                > label_values)
            :   dometer::metrics::observation<
                    /* duration */double,
                    /* error  */std::string,
                    /* qclass */dometer::dns::class_,
                    /* qname  */std::string,
                    /* qtype  */dometer::dns::type,
                    /* rcode  */std::string
                >::observation(
                    duration, label_values
                )
    {}

    lookup_observation_builder lookup_observation::new_builder() {
        return lookup_observation_builder();
    }

    dometer::metrics::observation<double,
                                  std::string,
                                  dometer::dns::class_,
                                  std::string,
                                  dometer::dns::type,
                                  std::string> lookup_observation_builder::build() const {
        return lookup_observation(_duration, std::make_tuple(_error, _qclass, _qname, _qtype, _rcode));
    }

    lookup_observation_builder& lookup_observation_builder::duration(double seconds) {
        this->_duration = seconds;
        return *this;
    }

    lookup_observation_builder& lookup_observation_builder::error(std::string error) {
        this->_error = error;
        return *this;
    }

    lookup_observation_builder& lookup_observation_builder::rcode(std::string rcode) {
        this->_rcode = rcode;
        return *this;
    }

    lookup_observation_builder& lookup_observation_builder::qclass(dometer::dns::class_ qclass) {
        this->_qclass = qclass;
        return *this;
    }

    lookup_observation_builder& lookup_observation_builder::qname(std::string qname) {
        this->_qname = qname;
        return *this;
    }

    lookup_observation_builder& lookup_observation_builder::qtype(dometer::dns::type qtype) {
        this->_qtype = qtype;
        return *this;
    }
}
