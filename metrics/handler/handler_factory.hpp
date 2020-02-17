#include "metrics/handler/handler.hpp"
#include "metrics/handler/options.hpp"

namespace dometer::metrics::handler {
    class HandlerFactory {
        public:
            static Handler makeHandler(Options options);
    };
}
