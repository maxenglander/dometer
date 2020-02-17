#include "metrics/observer.hpp"
#include "metrics/options.hpp"

namespace dometer::metrics {
    class ObserverFactory {
        public:
            static Observer makeObserver(Options options);
    };
}
