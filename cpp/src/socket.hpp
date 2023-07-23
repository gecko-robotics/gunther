
#pragma once


#include <errno.h>
#include <string>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_sockaddr


extern int errno; // don't like this global value
constexpr int SOCKET_ERR = -1;
constexpr int SOCKET_TIMEOUT = -1;
constexpr int SOCKET_OK = 0;

struct group_t {
  std::string addr;
  uint16_t port;
};

using sockaddr_t = struct sockaddr;
using inetaddr_t = struct sockaddr_in; // udp or tcp
using socket_fd_t = int; // socket descriptor

using message_t = std::vector<uint8_t>;

const inetaddr_t& inet_sockaddr(const std::string &addr, uint16_t port) {
  inetaddr_t inet;
  inet.sin_family      = AF_INET;
  inet.sin_addr.s_addr = inet_addr(addr.c_str());
  inet.sin_port        = htons(port);
  return std::move(inet);
}

const inetaddr_t& inet6_sockaddr(const std::string &addr, uint16_t port) {
  inetaddr_t inet;
  // inet.sin_family      = AF_INET6;
  // inet.sin_addr.s_addr = inet_addr(addr.c_str());
  // inet.sin_port        = htons(port);
  return std::move(inet);
}