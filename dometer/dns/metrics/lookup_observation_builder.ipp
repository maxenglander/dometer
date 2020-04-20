#pragma once

#include <string>

#include "dometer/dns/message/rcode.hpp"
#include "dometer/dns/record/class.hpp"
#include "dometer/dns/record/type.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/metrics/lookup_observation_builder.hpp"
#include "dometer/metrics/observation_builder.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::dns::metrics {
    lookup_observation_builder::lookup_observation_builder()
        : lookup_observation_builder("-")
    {}

    lookup_observation_builder::lookup_observation_builder(std::string placeholder_value)
        : dometer::metrics::observation_builder<double>::observation_builder(),
          _placeholder_value(placeholder_value)
    {
        label("error", _placeholder_value);
        label("rcode", _placeholder_value);
        label("qclass", _placeholder_value);
        label("qname", _placeholder_value);
        label("qtype", _placeholder_value);
    }

    lookup_observation_builder& lookup_observation_builder::duration(std::chrono::duration<double> duration,
                                                                     dometer::metrics::unit unit) {
        double _value = 0.0;
        switch(unit) {
            case dometer::metrics::unit::seconds:
                _value = std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
                break;
            default:
                _value = duration.count();
                break;
        }
        value(_value);
        return *this;
    }

    lookup_observation_builder& lookup_observation_builder::error(dometer::dns::resolver::error error) {
        label("error", dometer::dns::resolver::to_string(error.code));
        return *this;
    }

    lookup_observation_builder& lookup_observation_builder::qclass(dometer::dns::record::class_ qclass) {
        label("qclass", static_cast<std::string>(qclass));
        return *this;
    }

    lookup_observation_builder& lookup_observation_builder::qname(std::string qname) {
        label("qname", qname);
        return *this;
    }

    lookup_observation_builder& lookup_observation_builder::qtype(dometer::dns::record::type qtype) {
        label("qtype", static_cast<std::string>(qtype));
        return *this;
    }

    lookup_observation_builder& lookup_observation_builder::rcode(dometer::dns::message::rcode rcode) {
        label("rcode", static_cast<std::string>(rcode));
        return *this;
    }
}
