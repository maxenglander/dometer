#include <map>
#include <memory>
#include <string>
#include <tuple>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/label_helper.hpp"
#include "dometer/util/tuple_helper.hpp"

namespace util = dometer::util;

namespace dometer::metrics {
    class LabelWriter {
        public:
            LabelWriter(std::map<std::string, std::string>& labels) : labels(labels) {}
            template<typename T>
            void operator()(std::pair<std::shared_ptr<label<T>>, T> entry) const {
                auto label = entry.first;
                auto value = entry.second;
                labels[label->name] = label->to_string(value);
            }
        private:
            std::map<std::string, std::string>& labels;
    };

    template<typename... T>
    std::map<std::string, std::string> LabelHelper::createLabelMap(
            std::tuple<std::shared_ptr<label<T>>...> labels, std::tuple<T...> values) {
        std::map<std::string, std::string> result;
        LabelWriter labelWriter(result);
        auto zip = util::TupleHelper::zip(labels, values);

        constexpr int numLabels = sizeof...(T);
        for(int i = 0; i < numLabels; i++) {
            util::TupleHelper::visitAt(zip, i, labelWriter); 
        }

        return result;
    }
}
