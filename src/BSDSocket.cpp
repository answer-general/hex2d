#include "BSDSocket.hpp"

namespace net {

    bsd_tcp_socket::bsd_tcp_socket(int sockfd = -1) {
        sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sockfd < 0) {
            throw SocketCreateFailException();
        }
    }

    void bsd_tcp_socket::connect(const std::string& host, unsigned short port) {
        if (sockfd < 0) {
            throw InvalidSocketException();
        }

        int status;
        struct addrinfo hints;
        struct addrinfo *servinfo;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        if((status = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &servinfo)) != 0) {
            throw InvalidHostException();
        }

        if((servinfo->ai_next == NULL) && (servinfo != NULL)) {
            if(::connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) != 0) {
                freeaddrinfo(servinfo);
                throw HostNotReachableException();
            }
            freeaddrinfo(servinfo);
        } else {
            freeaddrinfo(servinfo);
            throw InvalidHostException();
        }
        return;
    }

    ssize_t bsd_tcp_socket::send(const void *src, size_t sz) {
        if(src == NULL) throw InvalidSourceBufferException();
        if(sz == 0) throw InvalidSourceBufferSizeException();
        if (sockfd < 0) {
            throw InvalidSocketException();
        }

        ssize_t ret = ::send(sockfd, src, sz, 0);
        if (ret < 0) {
            throw SendFailException();
        }

        return ret;
    }

    ssize_t bsd_tcp_socket::recv(void *dst, size_t sz) {
        if(dst == NULL) throw InvalidDestinationBufferException();
        if(sz == 0) throw InvalidDestinationBufferSizeException();
        if (sockfd < 0) {
            throw InvalidSocketException();
        }

        ssize_t ret = ::recv(sockfd, dst, sz, 0);
        if (ret < 0) {
            throw ReceiveFailException();
        }
        return ret;
    }

    int bsd_tcp_socket::close() {
        int ret = ::close(sockfd);

        if (ret < 0) {
          throw InvalidSocketException();
        }

        sockfd = -1;
        return ret;
    }

    int bsd_tcp_socket::get_sockfd() noexcept {
        return sockfd;
    }

    bsd_tcp_socket::~bsd_tcp_socket() {
      this->close();
    }

}
