#pragma once

#include <functional>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/prometheus/lru_map.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/summary.hpp"
#include "prometheus/counter.h"
#include "prometheus/registry.h"
#include "prometheus/summary.h"
#include "prometheus/x/types.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    class handler : public dometer::metrics::handler::handler {
        class cache_evictor {
            public:
                cache_evictor(std::unordered_map<std::string, ::prometheus::x::AnyFamilyRef>&,
                             ::prometheus::x::FamilyNameAndTimeSeriesCount&);
                template <class MetricPtr>
                void operator()(MetricPtr&&);
            private:
                std::unordered_map<std::string, ::prometheus::x::AnyFamilyRef>& metric_families;
                ::prometheus::x::FamilyNameAndTimeSeriesCount& meta;
        };

        public:
            handler(size_t,
                    std::shared_ptr<::prometheus::Registry>,
                    std::vector<std::shared_ptr<::prometheus::x::Transport>>);
            handler(lru_map,
                    std::shared_ptr<::prometheus::Registry>,
                    std::vector<std::shared_ptr<::prometheus::x::Transport>>);
            handler(const handler&);
            handler(handler&&) = delete;

            virtual void increment(const dometer::metrics::counter&, std::map<std::string, std::string>, uint64_t);
            virtual void record(const dometer::metrics::summary&, std::map<std::string, std::string>, double);
        private:
            template<typename T>
            void cache_metric(T* t, ::prometheus::x::FamilyNameAndTimeSeriesCount);

            template<typename T, typename BuilderFn>
            std::x::expected<::prometheus::x::FamilyRef<T>, util::error> get_or_build_metric_family(std::string, std::string, BuilderFn);

            lru_map metric_cache;
            std::unordered_map<std::string, ::prometheus::x::AnyFamilyRef> metric_families;
            std::shared_ptr<::prometheus::Registry> registry;
            std::vector<std::shared_ptr<::prometheus::x::Transport>> transports;
    };
}
