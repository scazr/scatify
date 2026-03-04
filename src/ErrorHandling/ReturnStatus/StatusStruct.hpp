#pragma once
#include <string>
#include "ErrorHandling/Failure/GenericFailure.hpp"

struct Success {
  constexpr explicit operator bool() const noexcept { return true; }
};

inline std::string show(const Success&) {
  return "Success";
}

template<typename FailureEnum = GenericFailure> requires std::is_enum_v<FailureEnum>
struct Failure {
  FailureEnum error_type{};
  std::string description{};

  Failure() = default;
  Failure(FailureEnum error_type) : error_type(error_type) {};
  Failure(FailureEnum error_type, std::string description) 
  : error_type(error_type),
    description(std::move(description)) {};

  constexpr explicit operator bool() const noexcept { return false; }
};

template<typename FailureEnum = GenericFailure> requires std::is_enum_v<FailureEnum>
inline std::string show(const Failure<FailureEnum> &failure) {
  return show(failure.error_type);
}
