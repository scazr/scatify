#include "ErrorHandling/ReturnStatus/ReturnStatus.hpp"

ReturnStatus<GenericFailure> fail(std::string description = "") {
  return Failure<GenericFailure>{ GenericFailure::failure, std::move(description) };
}
