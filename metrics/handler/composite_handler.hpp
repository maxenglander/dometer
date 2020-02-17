#include <vector>

namespace dometer::metrics::handler {
    class CompositeHandler {
        public:
            CompositeHandler(std::vector<Handler> handlers);
        private:
            std::vector<Handler> handlers;
    }
}
