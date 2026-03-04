#pragma once
#include <string>

enum class GenericFailure { failure };

inline std::string show(const GenericFailure&) {
  return "GenericFailure::failure";
}
