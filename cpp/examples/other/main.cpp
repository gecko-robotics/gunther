#include <iostream>
// #include <gunther.hpp>
#include <socket.hpp>
#include <string>

using namespace std;

int main() {
  inetaddr_t a = inet_sockaddr("udp://1.2.3.4:1234");
  cout << a << endl;

  // unixaddr_t b = unix_sockaddr("unix://./sock.uds");
  // cout << b << endl;

  // string s{"{\"URI\": \"udp://1.2.3.4:123\", \"TOPIC\": \"imu\", \"FORMAT\": \"msg_t\", \"SIZE\": 128}"};
  // message_t m = transform(s);
  // cout << m << endl;

  // dict d = decode2(m);
  // cout << d << endl;

  return 0;
}