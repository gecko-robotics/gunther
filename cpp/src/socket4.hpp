
#pragma once

#include "socket.hpp"
#include <unistd.h> // close


class Socket4 {
  public:
  Socket4(group_t grp, uint8_t ttl=1, int loopback=1): group(grp) {
    socket_fd = ::socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(IPPROTO_IP, IP_MULTICAST_TTL, ttl);
    setsockopt(IPPROTO_IP, IP_MULTICAST_LOOP, loopback);

    setsockopt(SOL_SOCKET, SO_REUSEADDR, 1);
    setsockopt(SOL_SOCKET, SO_REUSEPORT, 1);

    bound = false;
  }

  void bind() {
    inetaddr_t addr = inet_sockaddr("0.0.0.0", group.port);
    int err = ::bind(socket_fd, (const sockaddr_t *)&addr, sizeof(addr));
    guard(err);

    // mreq = struct.pack("=4sl", inet_aton(self.mcast_addr), INADDR_ANY);
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(group.addr.c_str()); // Multicast IP
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);// any interface
    // setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP, mreq);
    err = ::setsockopt(socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    guard(err);

    bound = true;
  }

  void close() {
    if (bound) {
      // mreq = struct.pack("=4sl", inet_aton(self.mcast_addr), INADDR_ANY)
      // setsockopt(SOL_IP, IP_DROP_MEMBERSHIP, mreq);
      struct ip_mreq mreq;
      mreq.imr_multiaddr.s_addr = inet_addr(group.addr.c_str()); // Multicast IP
      mreq.imr_interface.s_addr = htonl(INADDR_ANY);// any interface
      // setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP, mreq);
      ::setsockopt(socket_fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    }
    ::close(socket_fd);
  }

  void setsockopt(int level, int name, int val) {
    int err = ::setsockopt(socket_fd, level, name, (char *)&val, sizeof(val));
    guard(err);
  }

  message_t recvfrom(size_t msg_size, inetaddr_t *from_addr, const int flags=0) {
    message_t dst(msg_size);
    int num = 0;

    if (from_addr != NULL) {
      socklen_t from_len = sizeof(*from_addr);
      memset(from_addr, 0, from_len);
      num = ::recvfrom(socket_fd,
        dst.data(), msg_size,
        flags,
        (sockaddr_t*)from_addr, &from_len);
    }
    else
      num = ::recvfrom(socket_fd, dst.data(), msg_size, flags, NULL, NULL);

    // std::cout << "recvfrom done msg: " << dst.capacity() << " " << dst.size() << std::endl;

    // FIXME: add msg_size != dst.size() ???
    // timeout gives -1, so set size=0
    if (num == SOCKET_TIMEOUT || num == 0) dst.clear();

    return std::move(dst);
  }

  message_t recv(size_t msg_size, const int flags=0) {
    message_t m = recvfrom(msg_size,NULL,flags);
    return std::move(m);
  }

  int sendto(const message_t& msg, const inetaddr_t &addr, int flags=0) {
    // std::cout << "sendto" << std::endl;
    int num = ::sendto(
      socket_fd,
      msg.data(), msg.size(),
      flags,
      (struct sockaddr *)&addr, sizeof(addr));

    guard(msg.size() != num);
    // std::cout << "sendto done" << std::endl;
    return num;
  }

  const std::string mcast_addr{"224.0.0.251"};
  const uint16_t mcast_port{5353};

  protected:
  socket_fd_t socket_fd;
  group_t group;
  bool bound;

  inline void guard(int err) {
    if (err < 0) {
      this->close();
      // std::cout << msg + std::string(strerror(int(errno))) << std::endl;
      std::string msg = std::string(strerror(int(errno)));
      throw std::runtime_error(msg);
    }
  }
};