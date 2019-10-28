#include <map>
#include <memory>
#include <string>
#include <tuple>

#include "metrics/label.hpp"
#include "metrics/label_helper.hpp"
#include "util/tuple_helper.hpp"

namespace Util = Dometer::Util;

namespace Dometer::Metrics {
    class LabelWriter {
        public:
            LabelWriter(std::map<std::string, std::string>& labels) : labels(labels) {}
            template<typename T>
            void operator()(std::pair<std::shared_ptr<Label<T>>, T> entry) const {
                auto label = entry.first;
                auto value = entry.second;
                labels[label->name] = label->toString(value);
            }
        private:
            std::map<std::string, std::string>& labels;
    };

    template<typename... T>
    std::map<std::string, std::string> LabelHelper::createLabelMap(
            std::tuple<std::shared_ptr<Label<T>>...> labels, std::tuple<T...> values) {
        std::map<std::string, std::string> result;
        LabelWriter labelWriter(result);
        auto zip = Util::TupleHelper::zip(labels, values);

        constexpr int numLabels = sizeof...(T);
        for(int i = 0; i < numLabels; i++) {
            Util::TupleHelper::visitAt(zip, i, labelWriter); 
        }

        return result;
    }
}
