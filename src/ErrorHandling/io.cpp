#include <iostream>
#include "ErrorHandling/io.hpp"

using std::string;

void printcerr(string output, string end) {
  std::cerr << output << end;
}

void printcout(string output, string end) {
  std::cout << output << end;
}
