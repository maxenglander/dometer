#include <cstdio>
#include <fstream>
#include <stdexcept>

#include "cwrap/resolv_wrapper/builder.hpp"
#include "cwrap/resolv_wrapper/file.hpp"
#include "std/x/unique.hpp"

namespace cwrap::resolv_wrapper {
    hosts_builder builder::new_hosts_builder() {
        return hosts_builder();
    }

    hosts_builder& hosts_builder::add_a_record(std::string name, std::string data) {
        _records.push_back(name + " " + data);
        return *this;
    }

    resolv_wrapper hosts_builder::build() {
        char _template[MAXPATHLEN];
        std::string name(std::tmpnam(nullptr));
        auto stream = std::x::make_unique<std::fstream>(name, std::fstream::out);
        for(auto it = _records.begin(); it < _records.end(); it++) {
            *stream << *it << std::endl;
        }

        return resolv_wrapper(self_destructing_file(name, std::move(stream)), wrap_mode::hosts);
    }
}
