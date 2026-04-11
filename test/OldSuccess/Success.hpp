#pragma once
#include <string>

template<typename SuccessReturn = void>
struct Success {
private:
  SuccessReturn content;
public:
  Success(SuccessReturn content);
  SuccessReturn getContent();
  constexpr explicit operator bool() const noexcept { return true; }
};

template<>
struct Success<void> {
  Success() = default;
  constexpr explicit operator bool() const noexcept { return true; }
};

template<typename SuccessReturn>
Success<SuccessReturn> succeed(SuccessReturn content);

Success<void> succeed();

template<typename SuccessReturn>
inline std::string show(const Success<SuccessReturn>&);

#include "Success.tpp"
