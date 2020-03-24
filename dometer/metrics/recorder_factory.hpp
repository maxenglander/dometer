#include <memory>

#include "dometer/metrics/recorder.hpp"
#include "dometer/metrics/options.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::metrics {
    class recorder_factory {
        public:
            static std::x::expected<std::shared_ptr<recorder>, util::error> make_recorder(options);
    };
}
