#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <resolv.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <jsoncpp/json/json.h>

#define MAX_LINE      4096
#define SRV_BACKLOG   100

ssize_t
readline(int fd, void *vbuf, size_t n);

int
main(int argc, char **argv) {
    const char *srvsockpath = "/var/run/dns-telemeter.sock";

    struct sockaddr_un srvaddr;
    int clisockfd, srvsockfd;
    char line[MAX_LINE];
    int linelen;

    Json::Reader reader;
    Json::Value jsonin;
    Json::Value jsonout;
    Json::FastWriter writer;

    memset(&srvaddr, 0, sizeof(srvaddr));

    /******************************************/
    /* Initialize resolver system.            */
    /******************************************/
    if(res_init() < 0) {
        fprintf(stderr, "Failed to initialize resolver system with res_init(): %s (%d)\n",
                strerror(errno), errno);
    }

    /******************************************/
    /* Create a UNIX domain stream socket.    */
    /******************************************/
    srvsockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(srvsockfd < 0) {
        fprintf(stderr, "Failed to create unix domain socket: %s (%d)\n", strerror(errno), errno);
        exit(1);
    }
    fprintf(stdout, "Created a unix domain socket\n");

    /******************************************/
    /* Set up the UNIX sockaddr structure.    */
    /* by using AF_UNIX for the family and    */
    /* giving it a filepath to bind to.       */
    /*                                        */
    /* Unlink the file so that the bind will  */
    /* succeed, then bind to that file.       */
    /******************************************/
    srvaddr.sun_family = AF_UNIX;
    strncat(srvaddr.sun_path, srvsockpath, sizeof(srvaddr.sun_path) - 1);

    unlink(srvsockpath);
    if(bind(srvsockfd, (struct sockaddr *) &srvaddr, sizeof(srvaddr)) < 0) {
        fprintf(stderr, "Failed to bind socket: %s (%d)\n", strerror(errno), errno);
        close(srvsockfd);
        exit(1);
    }
    fprintf(stdout, "Bound the unix domain socket to: %s\n", srvsockpath);

    /******************************************/
    /* Listen for any client sockets          */
    /******************************************/
    if(listen(srvsockfd, SRV_BACKLOG) < 0) {
        fprintf(stderr, "Failed to listen for client connections: %s (%d)\n", strerror(errno), errno);
        close(srvsockfd);
        exit(1);
    }
    fprintf(stdout, "Listening for client connections\n");

    /******************************************/
    /* Accept incoming connections            */
    /******************************************/
    for(;;) {
        clisockfd = accept(srvsockfd, NULL, NULL);
        if(clisockfd < 0) {
            fprintf(stderr, "Failed to accept a client connection: %s (%d)\n", strerror(errno), errno);
            close(clisockfd);
            close(srvsockfd);
            exit(1);
        }
        fprintf(stdout, "Accepted a connection\n");

        while((linelen = readline(clisockfd, line, MAX_LINE)) > 0) {
            jsonout["result"] = Json::Value(false);

            if(!reader.parse(&(line[0]), &(line[linelen-1]), jsonin)) {
                fprintf(stderr, "Failed to parse JSON line: %s", line);
            } else {
                if(jsonin["method"] == "initialize") {
                    fprintf(stdout, "Initialization requested, nothing to do\n");
                    jsonout["result"] = Json::Value(true);
                }

                if(jsonin["method"] == "lookup") {
                    unsigned char answer[NS_PACKETSZ];
                    int anslen;
                    char *qname = &(jsonin["parameters"]["qname"].asString()[0]);
                    std::string qtype = jsonin["parameters"]["qtype"].asString();

                    if(qtype == "A") {
                        fprintf(stdout, "Looking up A record %s\n", qname);
                        if(anslen = res_search(qname, C_IN, T_A, answer, NS_PACKETSZ) < 0) {
                            fprintf(stderr, "Lookup of A record %s failed: %s (%d)\n", qname, strerror(errno), errno);
                        } else {
                            ns_msg handle;
                            ns_initparse(answer, anslen, &handle);
                            if(ns_msg_count(handle, ns_s_an) == 0) {
                            } else {
                            }
                        }
                    }
                }

                std::string response = writer.write(jsonout);
                fprintf(stdout, "Sending response: %s", &response[0]);
                if(send(clisockfd, &response[0], response.length(), 0) < 0) {
                    fprintf(stderr, "Failed to send response: %s (%d)\n", strerror(errno), errno);
                }
            }
        }

        fprintf(stderr, "Failed to read line from client socket: %s (%d)\n", strerror(errno), errno);
        close(clisockfd);
    }
}

ssize_t
readline(int fd, void *vbuf, size_t n) {
    ssize_t num_read;
    size_t tot_read;
    char *buf;
    char ch;

    if (n <= 0 || vbuf == NULL) {
        errno = EINVAL;
        return -1;
    }

    buf = (char *)vbuf;                 /* No pointer arithmetic on "void *" */

    tot_read = 0;
    for(;;) {
        num_read = read(fd, &ch, 1);    /* Read a single character from fd */
        if (num_read == -1) {
            if (errno == EINTR)         /* Interrupted -> restart read()   */
                continue;
            else
                return -1;              /* Some other error                */
        } else if (num_read == 0) {     /* EOF                             */
            if (tot_read == 0)          /* No bytes read; return 0         */
                return 0;
            else                        /* Some bytes read; add '\0'       */
                break;
        } else {                        /* 'num_read' must be 1            */
            if (tot_read < n - 1) {     /* Discard > (n - 1) bytes         */
                tot_read++;
                *buf++ = ch;
            }

            if (ch == '\n')
                break;
        }
    }

    *buf = '\0';
    return tot_read;
}
