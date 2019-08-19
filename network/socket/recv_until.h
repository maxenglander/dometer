#pragma once

#include <sys/types.h>

namespace DnsTelemeter::Network::Socket {
    ssize_t recvUntil(unsigned int fd, void *vbuf, char delimiter, size_t n);
}
