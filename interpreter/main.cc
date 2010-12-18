#pragma warning(disable: 4819)
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "compire.hpp"

int main() {
  std::ifstream fin("main.ypp");
  if (!fin) {
    std::cout << "入力ファイルを開けませんでした" << std::endl;
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
    std::cout << "コンパイルエラー" << std::endl;
  }
  return 0;
}