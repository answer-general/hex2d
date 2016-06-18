#ifndef BSD_SOCKET_HPP
#define BSD_SOCKET_HPP

#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <string>

namespace net {

class InvalidSocketException {};
class InvalidHostException {};
class InvalidSourceBufferException {};
class InvalidSourceBufferSizeException {};
class InvalidDestinationBufferException {};
class InvalidDestinationBufferSizeException {};
class SendFailException {};
class ReceiveFailException {};
class SocketCreateFailException {};
class HostNotReachableException {};


    class bsd_tcp_socket {
        public:
            bsd_tcp_socket(int sockfd);
            void connect(const std::string& host, unsigned short port);
            ssize_t send(const void *src, size_t sz);
            ssize_t recv(void *dst, size_t sz);
            int close();
            int get_sockfd() noexcept;
            ~bsd_tcp_socket();
        private:
            int sockfd = -1;
    };
}

#endif /* !BSD_SOCKET_HPP */
