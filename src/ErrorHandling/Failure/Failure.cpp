#include "Failure.hpp"

Failure fail() {
  return Failure();
}

inline std::string show(const Failure &) {
  return "Failure";
}
