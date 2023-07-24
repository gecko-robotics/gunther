#include <iostream>
#include <gunther.hpp>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {

  return 0;
}

  // inetaddr_t a = filter<inetaddr_t>("udp://1.2.3.4:1234");
  // cout << a << endl;

  // unixaddr_t b = filter<unixaddr_t>("unix://./sock.uds");
  // cout << b << endl;

//  string s{"{\"URI\": \"udp://1.2.3.4:123\", \"TOPIC\": \"imu\", \"FORMAT\": \"msg_t\", \"SIZE\": 128}"};
//   message_t m = transform(s);
//   cout << m << endl;

//   dict d = decode2(m);
//   cout << d << endl;

//   return 0;

  // int i = test<int>();
  // float f = test<float>();


  // Might be better
  // //------------------------------------------------
  // Ascii a;
  // dict d;
  // // string msg{"hello|9|1234|1.2.3.4"};
  // string msg{"{\"URI\": \"udp://1.2.3.4:123\", \"TOPIC\": \"imu\", \"FORMAT\": \"msg_t\", \"SIZE\": 128}"};
  // message_t s;
  // for (int i=0; i<msg.size(); i++) {
  //   if (msg[i] != '"' && msg[i] != '{' && msg[i] != ' ') s.push_back((uint8_t)msg[i]);
  // }
  // // string s = m.eat();
  // cout << "s: " << s << endl;

  // // vector<kv_t> kv;

  // size_t start=0, end=0, colon=0;
  // size_t i=0;
  // while (i<s.size()) {
  //   if (s[i] == ':') {
  //     colon = i;
  //     i++;
  //     while (i<s.size()) {
  //       if (s[i] == ',' || s[i] == '}') {
  //         end = i;
  //         std::string key(colon-start,0); //key.reserve(colon-start);
  //         std::string value(end-colon-1,0); //value.reserve(end-colon-1);
  //         // key.append(s, start, colon-start);
  //         // value.append(s, colon+1, end-colon-1); // skip :
  //         memcpy(key.data(), &s.data()[start], colon-start);
  //         memcpy(value.data(), &s.data()[colon+1], end-colon-1);
  //         d[key] = value;
  //         start = end+1; // skip ,
  //         break;
  //       }
  //       i++;
  //     }
  //   }
  //   i++;
  // }

  // cout << "New dict" << endl;
  // for (const auto& [key, value] : d) {
  //   cout << key << " -> " << value << endl;
  // }

  // //------------------------------------------------

// dict decode(const message_t& msg) {
//   dict d;
//   message_t s;
//   for (int i=0; i<msg.size(); i++) {
//     if (msg[i] != '"' && msg[i] != '{' && msg[i] != ' ') s.push_back((uint8_t)msg[i]);
//   }
//   // string s = m.eat();
//   cout << "s: " << s << endl;

//   // vector<kv_t> kv;

//   size_t start=0, end=0, colon=0;
//   size_t i=0;
//   while (i<s.size()) {
//     if (s[i] == ':') {
//       colon = i;
//       i++;
//       while (i<s.size()) {
//         if (s[i] == ',' || s[i] == '}') {
//           end = i;
//           std::string key(colon-start,0); //key.reserve(colon-start);
//           std::string value(end-colon-1,0); //value.reserve(end-colon-1);
//           // key.append(s, start, colon-start);
//           // value.append(s, colon+1, end-colon-1); // skip :
//           memcpy(key.data(), &s.data()[start], colon-start);
//           memcpy(value.data(), &s.data()[colon+1], end-colon-1);
//           d[key] = value;
//           start = end+1; // skip ,
//           break;
//         }
//         i++;
//       }
//     }
//     i++;
//   }
//   return d;
// }


// ostream& operator<<(ostream& s, const message_t& m) {
//   for (size_t i=0; i<m.size(); ++i) s << (char)m[i];
//   return s;
// }

// class msg_t: public std::vector<uint8_t> {
//   public:
//   std::string eat() {
//     std::string ret;
//     for (int i=0; i < size(); ++i) {
//       uint8_t v = this->operator[](i);
//       if (v != '"' && v != '{' && v != ' ') {
//         ret.push_back((char)v);
//       }
//     }
//     return ret;
//   }
// };

// bool kgetline()
// std::string eat(const std::string& s) {
//   std::string ret;
//   for (int i=0; i < s.size(); ++i) if (s[i] != '"' && s[i] != '{' && s[i] != ' ' && s[i] != '}') ret.push_back(s[i]);
//   return ret;
// }

// struct kv_t {
//   std::string key;
//   std::string value;
// };


// template<typename T> T test();

// template<>
// float test() {
//   float f = 1.234;
//   cout << "float: " << f << endl;
//   return f;
// }

// template<>
// int test() {
//   int f = 5;
//   cout << "int: " << f << endl;
//   return f;
// }

  // std::replace(msg.begin(), msg.end(), '{', ' ');
  // std::replace(msg.begin(), msg.end(), '}', ' ');
  // string m = eat(msg);

  // string s;
  // stringstream ss(m);

  // while (getline(ss, s, ',')) {
  //   // cout << s << endl;
  //   string k,v;
  //   stringstream sss(s);
  //   // while (getline(sss,t,':')) {
  //   //   cout << t << " ";
  //   // }
  //   getline(sss,k,':');
  //   // getline(sss,v,':');
  //   // std::replace(k.begin(), k.end(), '\"', ' ');
  //   // string kk;
  //   // for (int i=0; i< k.size(); ++i) if (k[i] != '"' && k[i] != '{' && k[i] != ' ') kk.push_back(k[i]);
  //   for (int i=k.size()+1; i< s.size(); ++i) if (s[i] != ' ') v.push_back(s[i]);
  //   cout << k << " -> " << v << endl;
  // }


  // message_t m = a.encode(msg);
  // string s = a.decode(m);

  // cout << (msg == s) << ": " << s << endl;
  // m.clear();

  // Json j;
  // dict d;
  // d["uri"] = "udp://1.2.3.4:1234";
  // d["format"] = "map_t";
  // d["size"] = "125";
  // m = j.encode(d);

  // dict dd = j.decode(m);
  // for (const auto& [key, value] : dd) {
  //   cout << key << ": " << value << endl;
  // }

  // cout << "works: " << (d == dd) << endl;

  // // for (const uint8_t& d: m) cout << (char)d;
  // // cout << endl;
  // m.clear();

  // Info info{"udp://1.2.3.4:123","imu","msg_t",128};
  // m = info.encode();
  // for (const uint8_t& d: m) cout << (char)d;
  // cout << endl;
  // cout << "size: " << m.size() << endl;



  // cout << "-------------------" << endl;
  // // std::string s;
  // d.clear();
  // s.clear();
  // bool key = true;
  // // bool value = false;
  // // bool notstr = false;
  // // std::string s;
  // string k;
  // char c;
  // // s.clear();

  // int i = 0;
  // while (i < m.size()) {
  //   c = m[i];
  //   if (c == '{' || c == ' ');
  //   else if (c == '"') {
  //     c = m[++i];
  //     while ( c != '"') {
  //       s.push_back(c);
  //       c = m[++i];
  //     }
  //   }
  //   else if (c == ':') {
  //     k = s;
  //     s.clear();
  //   }
  //   else if (c == ',' || c == '}') {
  //     d[k] = s;
  //     cout << k << ": " << s << endl;
  //     s.clear();
  //   }
  //   else s.push_back(c);

  //   i++;
  // }
  // for (const uint8_t& c: m) {
  //   if (c == '{' || c == '}' || c == ' ') continue;
  //   else if (c == '"') {
  //     if (str == false) { // start
  //       str = true;
  //       s.clear();
  //       continue;
  //     }
  //     if (str == true) {
  //       str = false;
  //     }
  //   }
  //   else if (c == ':') {
  //     k = str;
  //     key = false;
  //   }
  //   else if (c == ',') {
  //     d[k] = v;
  //   }
  // }
  // cout << s << endl;

//   return 0;
// }