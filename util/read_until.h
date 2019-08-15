#pragma once

#include <sys/types.h>

namespace DnsTelemeter::Util {
    ssize_t readUntil(int fd, void *vbuf, char delimiter, size_t n);
}
