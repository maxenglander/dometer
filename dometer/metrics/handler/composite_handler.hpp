#include <vector>

namespace dometer::metrics::handler {
    class composite_handler {
        public:
            composite_handler(std::vector<handler> handlers);
        private:
            std::vector<handler> handlers;
    }
}
