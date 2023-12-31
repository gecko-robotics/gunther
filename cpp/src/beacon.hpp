/**
MIT License

Copyright (c) 2018 Kevin J. Walchko

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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
  typedef std::function<void(T &)> callback_t;

  Beacon(group_t grp, uint8_t ttl=1, int loopback=1): sock(T(grp, ttl, loopback)) {}

  inline
  void loop(const callback_t& cb) { while (true) cb(sock); }
  inline
  void once(const callback_t& cb) { cb(sock); }
  inline
  void bind() { sock.bind(); }

  protected:
  T sock;
};