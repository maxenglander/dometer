#include <map>
#include <memory>
#include <string>
#include <tuple>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/label_helper.hpp"
#include "dometer/util/tuple_helper.hpp"

namespace util = dometer::util;

namespace dometer::metrics {
    class label_writer {
        public:
            label_writer(std::map<std::string, std::string>& labels) : labels(labels) {}
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
    std::map<std::string, std::string> label_helper::create_label_map(
            std::tuple<std::shared_ptr<label<T>>...> labels, std::tuple<T...> values) {
        std::map<std::string, std::string> result;
        label_writer _label_writer(result);
        auto zip = util::tuple_helper::zip(labels, values);

        constexpr int num_labels = sizeof...(T);
        for(int i = 0; i < num_labels; i++) {
            util::tuple_helper::visit_at(zip, i, _label_writer); 
        }

        return result;
    }
}
