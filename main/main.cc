#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define DEFAULT_SOCK_PATH "/var/run/dns-telemeter.sock"

int
main(int argc, char **argv) {
    struct sockaddr_un addr;
    int rc, sockfd;

    memset(&addr, 0, sizeof(addr));

    /******************************************/
    /* Create a UNIX domain stream socket.    */
    /******************************************/
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sockfd == -1) {
        fprintf(stderr, "Failed to create unix domain socket: %s (%d)\n", strerror(errno), errno);
        exit(1);
    }

    /******************************************/
    /* Set up the UNIX sockaddr structure.    */
    /* by using AF_UNIX for the family and    */
    /* giving it a filepath to bind to.       */
    /*                                        */
    /* Unlink the file so that the bind will  */
    /* succeed, then bind to that file.       */
    /******************************************/
    addr.sun_family = AF_INET;
    strncat(addr.sun_path, DEFAULT_SOCK_PATH, sizeof(addr.sun_path) - 1);

    unlink(DEFAULT_SOCK_PATH);
    rc = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    if(rc == -1) {
        fprintf(stderr, "Failed to bind socket: %s (%d)\n", strerror(errno), errno);
        close(sockfd);
        exit(1);
    }
}
