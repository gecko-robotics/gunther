// https://google.github.io/googletest/primer.html
#include <gtest/gtest.h>
#include <gunther.hpp>
#include <string>
#include <iostream>

using namespace std;


TEST(gunther, ascii) {
  try {
    Ascii a;
    string s{"hello|9|1234|1.2.3.4"};
    message_t m = a.encode(s);
    string ss = a.decode(m);

    EXPECT_TRUE(ss == s);
  }
  catch (...) {
    EXPECT_TRUE(false);
  }
}

TEST(gunther, json) {
  try {
    Json j;
    dict d;
    d["host"] = "uri://1.2.3.4:1234";
    d["format"] = "msg_t";
    d["topic"] = "navigation:vision"; // colons OK
    d["size"] = "125";
    message_t m = j.encode(d);

    dict dd = j.decode(m);
    cout << dd << endl;

    EXPECT_TRUE(d == dd);
  }
  catch (...) {
    EXPECT_TRUE(false); // some other error
  }
}

TEST(gunther, json_fail) {
  try {
    Json j;
    dict d;
    d["host"] = "uri://1.2.3.4:1234";
    d["format"] = "msg\"_t"; // bad, but survives
    d["topic"] = "navigation:vision,"; // comma
    d["size"] = "1,25"; // comma
    message_t m = j.encode(d);

    dict dd = j.decode(m);
    // cout << dd << endl;

    EXPECT_FALSE(d == dd);

    d.clear();
    m.clear();
    dd.clear();
    d["host"] = "uri://1.2.3.4:1234";
    d["format"] = "msg\"_t"; // bad
    d["topic"] = "navigation:vision";
    d["size"] = "1\"25"; // bad
    m = j.encode(d);

    dd = j.decode(m);
    // cout << dd << endl;

    EXPECT_FALSE(d == dd);
  }
  catch (...) {
    EXPECT_TRUE(false); // some other error
  }
}
