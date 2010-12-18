#pragma warning(disable: 4819)
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "compire.hpp"

int main() {
  std::ifstream fin("main.ypp");
  if (!fin) {
    std::cout << "���̓t�@�C�����J���܂���ł���" << std::endl;
    return -1;
  }
  const std::istream_iterator<char> begin = fin;
  fin >> std::noskipws;
  const std::string str(begin, std::istream_iterator<char>());
  yappy::compiler compiler;
  int result;
  if (compiler.compile(str.begin(), str.end(), result)) {
    std::cout << result << std::endl;
  } else {
    std::cout << "�R���p�C���G���[" << std::endl;
  }
  return 0;
}