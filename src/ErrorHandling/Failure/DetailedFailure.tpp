#pragma once
#include <type_traits>
#include "ErrorHandling/Failure/DetailedFailure.hpp"
#include "ErrorHandling/FailureStatus/GenericFailure.hpp"

template<typename FailureTypeEnum> requires std::is_enum_v<FailureTypeEnum>
inline DetailedFailure<FailureTypeEnum>::DetailedFailure(FailureTypeEnum error_type)
: error_type(error_type) {}

template<typename FailureTypeEnum> requires std::is_enum_v<FailureTypeEnum>
inline DetailedFailure<FailureTypeEnum>::DetailedFailure(FailureTypeEnum error_type, std::string description)
: error_type(error_type),
  description(std::move(description)) {}

template<typename FailureTypeEnum> requires std::is_enum_v<FailureTypeEnum>
bool DetailedFailure<FailureTypeEnum>::hasContent() const { return true; }

template<typename FailureTypeEnum> requires std::is_enum_v<FailureTypeEnum>
FailureTypeEnum DetailedFailure<FailureTypeEnum>::getFailureType() const { return this->error_type; }

template<typename FailureTypeEnum> requires std::is_enum_v<FailureTypeEnum>
const std::string& DetailedFailure<FailureTypeEnum>::getDescription() const { return this->description; }

// template<typename FailureTypeEnum> requires std::is_enum_v<FailureTypeEnum>
// std::tuple<FailureTypeEnum, std::string>
// DetailedFailure<FailureTypeEnum>::getFailureData() const {
//   return std::tuple<FailureTypeEnum, std::string> (this->error_type, this->description);
// }

template<typename FailureTypeEnum> requires std::is_enum_v<FailureTypeEnum>
DetailedFailure<FailureTypeEnum> fail(FailureTypeEnum error_type, std::string description) {
  return DetailedFailure<FailureTypeEnum>(error_type, description);
}

template<typename FailureTypeEnum> requires std::is_enum_v<FailureTypeEnum>
inline std::string show(const DetailedFailure<FailureTypeEnum> &failure) {
  if(failure.getDescription().empty()) return show(failure.getFailureType());
  else return show(failure.getFailureType()) + " - " + failure.getDescription();
}
