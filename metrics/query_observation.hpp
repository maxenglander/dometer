#pragma once

namespace Dometer::Metrics {
    class QueryObservationBuilder;

    class QueryObservation {
        public:
            QueryObservation() = delete;
            static QueryObservationBuilder newBuilder() const;
    };
}
