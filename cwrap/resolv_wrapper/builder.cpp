#include <fstream>
#include <iostream>
#include <stdexcept>

#include "cwrap/resolv_wrapper/builder.hpp"
#include "cwrap/resolv_wrapper/file.hpp"
#include "std/x/unique.hpp"

namespace cwrap::resolv_wrapper {
    conf_builder builder::new_conf_builder() {
        return conf_builder();
    }

    hosts_builder builder::new_hosts_builder() {
        return hosts_builder();
    }

    resolv_wrapper conf_builder::build() {
        file _file = file::make_temporary_file("w");

        for(auto it = _nameservers.begin(); it < _nameservers.end(); it++) {
            fprintf(&_file.handle(), "nameserver %s\n", it->c_str());
        }

        // Close file so resolv_wrapper can read from it.
        _file.close(); 

        return resolv_wrapper(std::move(_file), wrap_mode::conf);
    }

    conf_builder& conf_builder::add_nameserver(std::string nameserver) {
        _nameservers.push_back(nameserver);
        return *this;
    }

    hosts_builder& hosts_builder::add_a_record(std::string name, std::string data) {
        _records.push_back("A " + name + " " + data);
        return *this;
    }

    resolv_wrapper hosts_builder::build() {
        file _file = file::make_temporary_file("w");

        for(auto it = _records.begin(); it < _records.end(); it++) {
            fprintf(&_file.handle(), "%s\n", it->c_str());
        }

        // Close file so resolv_wrapper can read from it.
        _file.close(); 

        return resolv_wrapper(std::move(_file), wrap_mode::hosts);
    }
}
