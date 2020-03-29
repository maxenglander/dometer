#pragma once

#include "dometer/app/options.hpp"
#include "dometer/dns/server/server.hpp"
#include "dometer/util/error.hpp"

namespace dometer::app {
    class app {
        public:
            app(options, std::shared_ptr<dometer::dns::server::server>);
            void join();
            std::x::expected<void, dometer::util::error> start();
            void stop();
        private:
            dometer::app::options _options;
            std::shared_ptr<dometer::dns::server::server> _server;
    };
}
