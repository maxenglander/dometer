#pragma once

#include <string>
#include <tuple>

#include "metrics/observation.hpp"

namespace Dometer::Metrics {
    class QueryObservationBuilder : public ObservationBuilder<std::string, bool> {
        public:
            Observation<std::string, bool> build() const;
            QueryObservationBuilder& qname(std::string);
            QueryObservationBuilder& valid(bool);
        private:
            std::string _qname;
            bool _valid;
    };

    struct QueryObservation : Observation<std::string, bool> {
        QueryObservation(std::tuple<std::string, bool>, uint64_t);
        static QueryObservationBuilder newBuilder();
        using Builder = QueryObservationBuilder;
    };
}
