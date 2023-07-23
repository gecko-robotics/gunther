
#pragma once

#include <string>
#include <functional>
#include "socket4.hpp"
#include "socket6.hpp"
#include "transport.hpp"

template<typename T>
class Beacon {
  public:
  Beacon(group_t grp, uint8_t ttl=1, int loopback=1): sock(T(grp, ttl, loopback)) {}

  void broadcast() {}

  void listen() {}

  void stream() {}

  protected:
  Ascii handler;
  T sock;
};