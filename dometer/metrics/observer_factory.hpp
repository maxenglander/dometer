#include <memory>

#include "dometer/metrics/observer.hpp"
#include "dometer/metrics/options.hpp"

namespace dometer::metrics {
    class ObserverFactory {
        public:
            static std::shared_ptr<Observer> makeObserver(Options options);
    };
}
