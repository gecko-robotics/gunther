
#pragma once

#include <string>

class Ascii {
  public:
  message_t loads(std::string& msg) {
    message_t ret;
    return std::move(ret);
  }

  std::string dumps(message_t& msg) {
    return std::string();
  }
};