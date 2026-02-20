#pragma once
#include <variant>
#include <string>
#include <type_traits>

enum class FileFailure {
  failure = 1,
  inexistent_path,
  not_a_directory,
  not_a_file,
  permission_denied
};

struct Success {
  constexpr explicit operator bool() const noexcept { return true; }
};

template<typename FailureEnum>
requires std::is_enum_v<FailureEnum>
struct Failure {
  FailureEnum error_type;
  std::string description;
};

template<typename FailureEnum>
using ReturnStatus = std::variant<Success, Failure<FailureEnum>>;

template<typename FailureEnum>
ReturnStatus<FailureEnum> success() {
  return Success{};
}

template<typename FailureEnum>
ReturnStatus<FailureEnum> fail(FailureEnum error_type, std::string description = "") {
  return Failure<FailureEnum>{ error_type, std::move(description) };
}
