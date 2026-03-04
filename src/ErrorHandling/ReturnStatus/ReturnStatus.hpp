#pragma once
#include <string>
#include <type_traits>
#include <variant>
#include "ErrorHandling/ReturnStatus/StatusStruct.hpp"


template<typename FailureEnum> requires std::is_enum_v<FailureEnum>
class ReturnStatus{
  std::variant<Success, Failure<FailureEnum>> data;

public:
  ReturnStatus(Success s) : data(s) {}
  ReturnStatus(Failure<FailureEnum> f) : data(std::move(f)) {}

  constexpr explicit operator bool() const noexcept {
    return std::holds_alternative<Success>(data);
  }

  bool holdsSuccess() const {
    return std::holds_alternative<Success>(data);
  }

  Failure<FailureEnum>& unsafeGetFailure() {
    return std::get<Failure<FailureEnum>>(data);
  }
};

template<typename FailureEnum>
ReturnStatus<FailureEnum> success() {
  return Success{};
}

template<typename FailureEnum>
ReturnStatus<FailureEnum> fail(FailureEnum error_type, std::string description = "") {
  return Failure<FailureEnum>{ error_type, std::move(description) };
}

template<typename FailureEnum> requires std::is_enum_v<FailureEnum>
std::string show(ReturnStatus<FailureEnum>& return_status) {
  if(return_status.holdsSuccess())
    return "Success";
  else
    return show(return_status.unsafeGetFailure());
}

