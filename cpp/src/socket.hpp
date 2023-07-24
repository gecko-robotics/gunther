
#pragma once

#ifndef __GECKO_SOCKET_HPP__
#define __GECKO_SOCKET_HPP__

// #include <errno.h>
#include <string>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_sockaddr
#include <ostream>
#include <ostream>
#include <regex>
#include <sys/un.h>     // UDS


// extern int errno; // don't like this global value
constexpr int SOCKET_ERR = -1;
constexpr int SOCKET_TIMEOUT = -1;
constexpr int SOCKET_OK = 0;
constexpr uint32_t AF_ERROR = 100;

struct group_t {
  std::string addr;
  uint16_t port;
};

using sockaddr_t = struct sockaddr;
using inetaddr_t = struct sockaddr_in; // udp or tcp
using unixaddr_t = struct sockaddr_un; // uds
using socket_fd_t = int; // socket descriptor

using message_t = std::vector<uint8_t>;

static
std::ostream& operator<<(std::ostream& s, const message_t& m) {
  for (size_t i=0; i<m.size(); ++i) s << (char)m[i];
  return s;
}

static
message_t transform(const std::string& msg) {
  message_t s;
  for (int i=0; i<msg.size(); i++) {
    // if (msg[i] != '"' && msg[i] != '{' && msg[i] != ' ')
    s.push_back((uint8_t)msg[i]);
  }
  return s;
}

static
const inetaddr_t& inet_sockaddr(const std::string &addr, uint16_t port) {
  inetaddr_t inet = {0};
  inet.sin_family      = AF_INET;
  inet.sin_addr.s_addr = inet_addr(addr.c_str());
  inet.sin_port        = htons(port);
  return std::move(inet);
}

inline
const inetaddr_t& inet_sockaddr(const group_t grp) {
  return inet_sockaddr(grp.addr, grp.port);
}

static
const inetaddr_t& inet6_sockaddr(const std::string &addr, uint16_t port) {
  inetaddr_t inet = {0};
  return std::move(inet);
}

static
std::string inet2string(const inetaddr_t &addr) {
  char ip[32] = {0};

  if (addr.sin_family == AF_INET) {
    ::inet_ntop(AF_INET, &(addr.sin_addr),ip,sizeof(ip));
    std::string host(ip,strlen(ip));
    host += ":" + std::to_string(ntohs(addr.sin_port));
    return host;
  }
  else if (addr.sin_family == AF_INET6) { return "ipv6 unsupported"; }
  return "not inet";
}

static
std::ostream& operator<<(std::ostream &os, inetaddr_t const &s) {
  os << inet2string(s);
  return os;
}

static
std::string unix2string(const unixaddr_t &addr) {
  if (addr.sun_family == AF_UNIX) return std::string(addr.sun_path);
  return "not unix";
}

static
std::ostream &operator<<(std::ostream &os, unixaddr_t const &s) {
  os << "File: " << unix2string(s);
  return os;
}


template<typename T>
static
const T filter(const std::string& address);

template<>
const inetaddr_t filter(const std::string& address) {
  std::regex proto("(udp|tcp)\\:\\/\\/([a-z,A-Z,\\d,\\/,.,*,_,-,:]+)");
  std::smatch m;

  // find [original, protocol, path|ip:port]
  regex_search(address, m, proto);
  inetaddr_t ans{0};
  ans.sin_family = AF_ERROR;

  if (m.size() != 3) return ans;
  if (m[1] == "tcp") return ans; // not handling tcp right now
  if (m[1] != "udp") return ans;

  uint16_t port;
  uint32_t ip;
  std::string ss = m[2];
  std::regex ipport("([a-z,A-Z,\\d,\\/,.,*]+):([*,\\d]+)");
  std::smatch mm;

  // find [original, ip, port]
  regex_search(ss, mm, ipport);
  if (mm.size() != 3) return ans; //return std::move(ans);

  else if (mm[1] == "*") ip = INADDR_ANY;
  else if (mm[1] == "bc") ip = INADDR_BROADCAST;
  else ip = inet_addr(mm[1].str().c_str());

  if (mm[2] == "*") port = 0;
  else port = stoi(mm[2]);

  ans.sin_family      = AF_INET;
  ans.sin_addr.s_addr = ip;
  ans.sin_port        = htons(port);
  // return std::move(ans);
  return ans;
}


template<>
const unixaddr_t filter(const std::string& address) {
  std::regex proto("(unix)\\:\\/\\/([a-z,A-Z,\\d,\\/,.,*,_,-,:]+)");
  std::smatch m;

  // find [original, protocol, path|ip:port]
  regex_search(address, m, proto);
  unixaddr_t ans{0};

  if (m.size() != 3 || m[1] != "unix") return std::move(ans);
  std::string path = m[2];

  ans.sun_family = AF_UNIX;
  strncpy(ans.sun_path, path.c_str(), path.size());
  return ans;
  // return std::move(ans);
}

const inetaddr_t& inet_sockaddr(const std::string &path) {
  return std::move(filter<inetaddr_t>(path));
}

const unixaddr_t& unix_sockaddr(const std::string &path) {
  return std::move(filter<unixaddr_t>(path));
}

#endif // geko_socket_hpp