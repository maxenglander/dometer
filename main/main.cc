#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "network/dns/resolver.h"
#include "network/socket/unix_socket.h"
#include "powerdns/unix_socket_remote_backend.h"
#include "std/experimental/expected.h"

#define MAX_LINE      4096
#define SRV_BACKLOG   100

using namespace DnsTelemeter;
using namespace DnsTelemeter::Network::Socket;
using namespace std::experimental;

ssize_t
readline(int fd, void *vbuf, size_t n);

int
main(int argc, char **argv) {
    PowerDns::UnixSocketRemoteBackend pdnsBackend;
    pdnsBackend.serve();

    /**
    Json::Reader reader;
    Json::Value jsonin;
    Json::Value jsonout;
    Json::FastWriter writer;
    */

    /*
    for(;;) {
        fprintf(stdout, "Waiting to accept a client connection\n");
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
                    std::string qname = jsonin["parameters"]["qname"].asString();
                    std::string qtype = jsonin["parameters"]["qtype"].asString();
                    Network::Dns::Resolver resolver;

                    if(qtype == "A") {
                        expected<Network::Dns::Result, int> result = resolver.lookupA(qname);
                        if(result) {
                            std::vector<Network::Dns::Answer> answers = (*result).getAnswers();
                            jsonout["result"] = Json::Value(Json::arrayValue);
                            for(std::vector<Network::Dns::Answer>::iterator it = answers.begin(); it != answers.end(); ++it) {
                                Json::Value jsonanswer(Json::objectValue);
                                jsonanswer["qtype"] = qtype;
                                jsonanswer["qname"] = qname;
                                jsonanswer["content"] = (*it).getContent();
                                jsonanswer["ttl"] = (*it).getTtl();
                                jsonout["result"].append(jsonanswer);
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
    */
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
