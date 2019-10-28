#include <map>
#include <memory>
#include <string>
#include <tuple>

#include "metrics/label.hpp"
#include "metrics/label_helper.hpp"
#include "util/tuple_helper.hpp"

namespace Dometer::Metrics {
    template<typename... T>
    std::map<std::string, std::string> createLabelMap(
            std::tuple<std::shared_ptr<Label<T>>...> labels, std::tuple<T...> values) {
        std::map<std::string, std::string> labelValueMap;

        for(int i = 0; i < sizeof...(T); i++) {
            labelValueMap.emplace(TupleHelper::applyAt(labels, i, [&values, i](auto label) {
                TupleHelper::applyAt(values, i, [&label](auto value) {
                    return std::make_pair(label.name, label.toString(value));
                });
            }));
        }

        return labelValueMap;
    }
}
