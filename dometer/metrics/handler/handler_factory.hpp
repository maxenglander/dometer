#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/options.hpp"

namespace dometer::metrics::handler {
    class HandlerFactory {
        public:
            static Handler makeHandler(Options options);
    };
}
