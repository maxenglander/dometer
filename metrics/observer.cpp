#include "metrics/handler.hpp"
#include "metrics/observer.hpp"

namespace Dometer::Metrics {
    Observer::Observer(Handler& handler) : handler(handler) {}
}
