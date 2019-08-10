#include <cstring>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "std/experimental/expected.h"

#include "powerdns/unix_socket_backend.h"

#define MAX_LINE 4096

using namespace std::experimental;

namespace DnsTelemeter::PowerDns {
    UnixSocketBackend::UnixSocketBackend(std::string socketPath, unsigned int maxConnections) {
        this->socketPath = socketPath;
        this->maxConnections = maxConnections;
    }

    std::string makeSocketError(std::string description) {
        return description + ": " + std::string(strerror(errno)) + "(" + std::to_string(errno) + ")";
    }

    expected<void, std::string> UnixSocketBackend::serve() {
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
        if(srvsockfd < 0) {
            return unexpected(this->makeSocketError("Failed to create unix domain socket"));
        }

        /******************************************/
        /* Set up the UNIX sockaddr structure.    */
        /* by using AF_UNIX for the family and    */
        /* giving it a filepath to bind to.       */
        /*                                        */
        /* Unlink the file so that the bind will  */
        /* succeed, then bind to that file.       */
        /******************************************/
        srvaddr.sun_family = AF_UNIX;
        strncat(srvaddr.sun_path, this->socketPath.c_str(), sizeof(srvaddr.sun_path) - 1);

        unlink(this->socketPath.c_str());
        if(bind(srvsockfd, (struct sockaddr *) &srvaddr, sizeof(srvaddr)) < 0) {
            close(srvsockfd);
            return unexpected(this->makeSocketError("Failed to bind socket"));
        }

        /******************************************/
        /* Listen for any client sockets          */
        /******************************************/
        if(listen(srvsockfd, this->maxConnections) < 0) {
            close(srvsockfd);
            return unexpected(this->makeSocketError("Failed to listen fo client connections"));
        }

        /******************************************/
        /* Accept incoming connections            */
        /******************************************/
        for(;;) {
            clisockfd = accept(srvsockfd, NULL, NULL);
            if(clisockfd < 0) {
                close(clisockfd);
                close(srvsockfd);
                return unexpected(this->makeSocketError("Failed to listen fo client connections"));
            }
        }
    }
}
