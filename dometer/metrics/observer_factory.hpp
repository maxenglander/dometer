#include <memory>

#include "dometer/metrics/observer.hpp"
#include "dometer/metrics/options.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::metrics {
    class observer_factory {
        public:
            static std::x::expected<std::shared_ptr<observer>, util::error> make_observer(options);
    };
}
