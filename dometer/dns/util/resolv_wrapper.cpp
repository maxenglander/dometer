#include <cassert>
#include <memory>

#include "dometer/dns/util/resolv_wrapper.hpp"
#include "dometer/util/error.hpp"

namespace dometer::dns::util {
    std::mutex resolv_wrapper::_mutex = {};

    resolv_wrapper::resolv_wrapper(std::mutex& mutex)
        : _lock(mutex, std::adopt_lock)
    {}

    resolv_wrapper::~resolv_wrapper() {}

    std::unique_ptr<resolv_wrapper> resolv_wrapper::make_resolv_wrapper() {
        std::unique_lock<std::mutex> lock(_mutex);
        lock.release();
        return std::unique_ptr<resolv_wrapper>(new resolv_wrapper(_mutex));
    }
}
