#pragma once

#include <sys/types.h>

namespace Dometer::Network::Socket {
    ssize_t recvUntil(unsigned int fd, void *vbuf, char delimiter, size_t n);
}
