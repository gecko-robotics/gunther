
#pragma once

// #include <iostream>
#include <errno.h>
#include <string>
// #include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Socket4 {
  public:
  Socket4() {
    ;
  }

  protected:
  const std::string mcast_addr{"224.0.0.251"};
  const uint16_t mcast_port{5353};
};