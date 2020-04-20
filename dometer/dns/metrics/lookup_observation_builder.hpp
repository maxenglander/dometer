#pragma once

#include <chrono>
#include <string>

#include "dometer/dns/message/rcode.hpp"
#include "dometer/dns/record/class.hpp"
#include "dometer/dns/record/type.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/metrics/observation_builder.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::dns::metrics {
    class lookup_observation_builder : private dometer::metrics::observation_builder<double> {
        public:
            lookup_observation_builder();
            lookup_observation_builder(std::string);
            lookup_observation_builder& duration(std::chrono::duration<double>, dometer::metrics::unit);
            lookup_observation_builder& error(dometer::dns::resolver::error);
            lookup_observation_builder& qclass(dometer::dns::record::class_);
            lookup_observation_builder& qname(std::string);
            lookup_observation_builder& qtype(dometer::dns::record::type);
            lookup_observation_builder& rcode(dometer::dns::message::rcode);
            using dometer::metrics::observation_builder<double>::build;
        private:
            std::string _placeholder_value;
    };
}

#include "dometer/dns/metrics/lookup_observation_builder.ipp"
