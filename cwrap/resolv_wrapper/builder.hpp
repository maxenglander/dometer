#pragma once

#include <vector>

#include "cwrap/resolv_wrapper/resolv_wrapper.hpp"

namespace cwrap::resolv_wrapper {
    class conf_builder;
    class hosts_builder;

    class builder {
        public:
            static hosts_builder new_hosts_builder();
            static conf_builder new_conf_builder();
            virtual resolv_wrapper build() = 0;
    };

    class conf_builder : public builder {
        public:
            conf_builder& add_nameserver(std::string);
            resolv_wrapper build();
        private:
            std::vector<std::string> _nameservers;
    };

    class hosts_builder : public builder {
        public:
            hosts_builder& add_a_record(std::string, std::string);
            resolv_wrapper build();
        private:
            std::vector<std::string> _records;
    };
}
