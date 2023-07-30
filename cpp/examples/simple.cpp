#include <iostream>
#include <ostream>
#include <gunther.hpp>
#include <vector>
#include <string>

using namespace std;


void func_broadcast(Socket4& sock) {
  Ascii a;
  message_t msg = a.encode("Hi how are you 1.2.3.4:56789");

  while (true) {
    sock.send(msg);

    cout << "." << std::flush;

    msleep(1000);
  }
  cout << endl;
}

void func_print(Socket4& sock) {
  Ascii a;
  while (true) {
    message_t msg = sock.recv(128);
    string m = a.decode(msg);
    cout << m << endl;
  }
}

int main(int args, char *argv[]) {
  if (args != 2) {
    cout << "Wrong arguments:" << endl;
    cout << "./main b|s" << endl;
  }
  char choice = argv[1][0];

  group_t grp{"224.0.0.251",5353};
  Beacon<Socket4> b(grp);

  switch (choice) {
    case 'b':
      b.loop(func_broadcast);
      break;
    case 's':
      b.bind();
      b.once(func_print);
      break;
    default:
      cout << "Invalide choice: " << choice << endl;
  }

  return 0;
}