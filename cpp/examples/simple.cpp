#include <iostream>
#include <gunther.hpp>
#include <vector>

using namespace std;

int main() {
  group_t grp{"224.0.0.251",5353};
  Beacon<Socket4> b(grp);

  vector<message_t> msgs {
    {'h','e','l','l','o','|','9'}
  };

  b.broadcast(msgs);

  return 0;
}