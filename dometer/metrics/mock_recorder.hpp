#pragma once

#include <map>
#include <string>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/histogram.hpp"
#include "dometer/metrics/recorder.hpp"
#include "gmock/gmock.h"

namespace dometer::metrics {
    class mock_recorder : public recorder {
        public:
            mock_recorder() {}
            MOCK_METHOD(void, increment, (const counter&, (std::map<std::string, std::string>), uint64_t));
            MOCK_METHOD(void, record, (const histogram&, (std::map<std::string, std::string>), double));
    };
}
