#pragma once

#include <map>
#include <string>

#include "dometer/metrics/observation.hpp"

namespace dometer::metrics {
    template <typename T>
    class observation_builder {
        public:
            observation_builder();
            observation_builder(const observation_builder&);
            observation_builder(observation_builder&&) = delete;
            virtual const observation<T> build() const; 
            virtual observation_builder<T>& label(std::string, std::string);
            virtual observation_builder<T>& value(T);
        private:
            std::map<std::string, std::string> _labels;
            T _value;
    };
}

#include "dometer/metrics/observation_builder.ipp"
