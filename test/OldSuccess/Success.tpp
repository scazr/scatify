#pragma once
#include "Success.hpp"

template<typename SuccessReturn>
Success<SuccessReturn>::Success(SuccessReturn content) {
  this->content = content;
}

template<typename SuccessReturn>
Success<SuccessReturn> succeed(SuccessReturn content) {
  return Success<SuccessReturn>(content);
}

inline Success<void> succeed() {
  return Success<void>{};
}

template<typename SuccessReturn>
inline std::string show(const Success<SuccessReturn>&) {
  return "Success";
}
