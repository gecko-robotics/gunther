#include <iostream>
#include <gunther.hpp>

int main() {
  group_t grp{"224.0.0.251",5353};
  Beacon<Socket4> b(grp);
  return 0;
}