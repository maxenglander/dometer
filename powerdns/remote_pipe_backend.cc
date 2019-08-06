#include <cstring>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>

#include "powerdns/remote_pipe_backend.h"

#define MAX_LINE 4096

namespace DnsTelemeter::PowerDns {
    RemotePipeBackend::RemotePipeBackend(std::string path) {
        this->path = path;
    }

    void RemotePipeBackend::run() {
        struct sockaddr_un srvaddr;
        int clisockfd, srvsockfd;
        char line[MAX_LINE];
        int linelen;

        /******************************************/
        /* Zero out the server socket address.    */
        /******************************************/
        memset(&srvaddr, 0, sizeof(srvaddr));

        /******************************************/
        /* Create a UNIX domain stream socket.    */
        /******************************************/
        srvsockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    }
}
