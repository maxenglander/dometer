#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>

#define SERV_PORT 53

int
main(int argc, char **argv) {
    struct sockaddr_in servaddr;
    int sockfd;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&servaddr, sizeof(servaddr), 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
}
