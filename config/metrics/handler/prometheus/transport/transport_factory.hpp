#pragma once

#include "config/metrics/handler/prometheus/transport/exposer_factory.hpp"
#include "config/metrics/handler/prometheus/transport/transport.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler::prometheus::transport {
    class TransportFactory {
        public:
            TransportFactory();
            TransportFactory(dometer::config::metrics::handler::prometheus::transport::ExposerFactory);
            Transport fromJson(const rapidjson::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::prometheus::transport::ExposerFactory exposerFactory;
    };
}
