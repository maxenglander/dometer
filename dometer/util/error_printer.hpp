#include <ostream>

#include "dometer/util/error.hpp"

namespace dometer::util {
    class ErrorPrinter {
        public:
            ErrorPrinter(std::ostream);
            void print(Error);
    };
}
