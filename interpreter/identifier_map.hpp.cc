#include "identifier_map.hpp"
#include <iostream>
#include <unordered_map>

namespace yappy {

namespace {
std::unordered_map<std::string, int> identifier_map;
}

void set_val(const std::string &name, int val) {
  identifier_map.insert(std::make_pair(name, val));
  std::cout << name << ":" << val << std::endl;
}

int get_val(const std::string &name) {
  auto it = identifier_map.find(name);
  if (it != identifier_map.end()) {
    return it->second;
  }
  throw std::exception();
  return 0;
}
}