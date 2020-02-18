#include <memory>

#include "metrics/observer.hpp"
#include "metrics/options.hpp"

namespace dometer::metrics {
    class ObserverFactory {
        public:
            static std::shared_ptr<Observer> makeObserver(Options options);
    };
}
