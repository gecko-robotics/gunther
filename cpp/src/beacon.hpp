
#pragma once

#include <string>
#include <functional>
#include "socket4.hpp"
#include "socket6.hpp"
#include "transport.hpp"
#include <thread>
#include <chrono> // time: sec, msec, usec

inline void msleep(int msec) {
  std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

template<typename T>
class Beacon {
  public:
  Beacon(group_t grp, uint8_t ttl=1, int loopback=1): sock(T(grp, ttl, loopback)) {}

  void broadcast(std::vector<message_t>& msgs, size_t delay=1000) {
    while (true) {
      for (const message_t& m: msgs) {
        sock.send(m);
      }

      msleep(delay);
    }
  }

  void listen() {}

  void stream() {}

  protected:
  Ascii handler;
  T sock;
};