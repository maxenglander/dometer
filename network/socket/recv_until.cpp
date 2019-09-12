#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "network/socket/recv_until.hpp"

namespace Dometer::Network::Socket {
    ssize_t recvUntil(unsigned int fd, void *vbuf, char delimiter, size_t n) {
        ssize_t num_read;
        size_t tot_read;
        char *buf;
        char ch;

        if(n <= 0 || vbuf == NULL) {
            errno = EINVAL;
            return -1;
        }

        buf = (char *)vbuf;                 /* No pointer arithmetic on "void *" */
        tot_read = 0;
        for(;;) {
            num_read = recv(fd, &ch, 1,
                            MSG_NOSIGNAL);  /* Read a single character from fd   */
            if(num_read == -1) {
                if(errno == EINTR)          /* Interrupted -> restart read()     */
                    continue;
                else {
                    return -1;              /* Some other error                  */
                }
            } else if(num_read == 0) {      /* EOF                               */
                if(tot_read == 0) {
                    return 0;               /* Some bytes read; add '\0'         */
                } else
                    break;
            } else {                        /* 'num_read' must be 1              */
                if(tot_read < n - 1) {      /* Discard > (n - 1) bytes          */
                    tot_read++;
                    *buf++ = ch;
                }

                if(ch == delimiter)
                    break;
            }
        }

        *buf = '\0';
        return tot_read;
    }
}
