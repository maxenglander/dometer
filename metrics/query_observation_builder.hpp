#pragma once

namespace Dometer::Metrics {
    class QueryObservation;

    class QueryObservationBuilder {
        public:
            QueryObservation build();
    };
}
