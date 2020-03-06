#include <memory>

#include "dometer/metrics/observer.hpp"
#include "dometer/metrics/options.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::metrics {
    class ObserverFactory {
        public:
            static std::x::expected<std::shared_ptr<observer>, util::error> makeObserver(Options options);
    };
}
