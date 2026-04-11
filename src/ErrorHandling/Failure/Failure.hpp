#pragma once
#include <string>

class Failure {
public:
  Failure() = default;

  constexpr explicit operator bool() const noexcept { return false; }
};

Failure fail();

inline std::string show(const Failure &failure);

