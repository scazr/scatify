#pragma once

class Success {
public:
  constexpr explicit operator bool() const noexcept { return true; }
  bool hasContent() const { return false;};
};

inline Success succeed() {
  return Success();
};
