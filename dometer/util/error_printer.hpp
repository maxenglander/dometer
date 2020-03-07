#include <ostream>

#include "dometer/util/error.hpp"

namespace dometer::util {
    class error_printer {
        public:
            error_printer(std::ostream);
            void print(error);
    };
}
