#pragma once

#include <string>
#include <tuple>

#include "metrics/observation.hpp"

namespace Dometer::Metrics {
    class QueryObservationBuilder : public ObservationBuilder<std::string, std::string, std::string, bool> {
        public:
            Observation<std::string, std::string, std::string, bool> build() const;
            QueryObservationBuilder& qclass(std::string);
            QueryObservationBuilder& qname(std::string);
            QueryObservationBuilder& qtype(std::string);
            QueryObservationBuilder& valid(bool);
        private:
            std::string _qclass;
            std::string _qname;
            std::string _qtype;
            bool _valid;
    };

    struct QueryObservation : Observation<std::string, std::string, std::string, bool> {
        QueryObservation(std::tuple<std::string, std::string, std::string, bool>, uint64_t);
        static QueryObservationBuilder newBuilder();
        using Builder = QueryObservationBuilder;
    };
}
