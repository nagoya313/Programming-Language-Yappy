#pragma once
#include <string>

namespace yappy {
void set_val(const std::string &name, int val);
int get_val(const std::string &name);
}