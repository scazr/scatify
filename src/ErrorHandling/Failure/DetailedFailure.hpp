#pragma once
#include <string>
#include <ErrorHandling/FailureStatus/GenericFailure.hpp>
#include <ErrorHandling/Failure/Failure.hpp>

template<typename FailureTypeEnum = GenericFailure> requires std::is_enum_v<FailureTypeEnum>
class DetailedFailure : public Failure {
  FailureTypeEnum error_type{};
  std::string description{};

public:
  DetailedFailure() = default;
  DetailedFailure(FailureTypeEnum error_type);
  DetailedFailure(FailureTypeEnum error_type, std::string description);

  bool hasContent() const;
  FailureTypeEnum getFailureType() const;
  const std::string& getDescription() const;
  // std::tuple<FailureTypeEnum, std::string> getFailureData() const;
};

template<typename FailureTypeEnum> requires std::is_enum_v<FailureTypeEnum>
DetailedFailure<FailureTypeEnum> fail(FailureTypeEnum error_type, std::string description);

template<typename FailureTypeEnum> requires std::is_enum_v<FailureTypeEnum>
inline std::string show(const DetailedFailure<FailureTypeEnum> &failure);

#include "DetailedFailure.tpp"
