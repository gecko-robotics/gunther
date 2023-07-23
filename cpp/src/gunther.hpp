
#pragma once


#include <arpa/inet.h> // for sockaddr_in
#include <sys/types.h>  // for type definitions like size_t
#include <string>
#include <vector>
#include <stdint.h>
#include <sys/socket.h> // socket, connect, etc ...

// using sockaddr_t = struct sockaddr;
// // using sockaddr_in_t = struct sockaddr_in;
// using inetaddr_t = struct sockaddr_in; // udp or tcp
// // using unixaddr_t = struct sockaddr_un; // uds
// using socket_fd_t = int; // socket descriptor

// using message_t = std::vector<uint8_t>;

// const inetaddr_t& inet_sockaddr(const std::string &addr, uint16_t port) {
//   inetaddr_t inet;

//   inet.sin_family      = AF_INET;
//   inet.sin_addr.s_addr = inet_addr(addr.c_str());
//   inet.sin_port        = htons(port);

//   return std::move(inet);
// }

#include "socket4.hpp"
#include "socket6.hpp"
#include "transport.hpp"
#include "beacon.hpp"