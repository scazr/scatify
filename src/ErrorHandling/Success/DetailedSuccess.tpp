#pragma once
#include <string>
#include "ErrorHandling/Success/DetailedSuccess.hpp"

template<typename ContentType>
DetailedSuccess<ContentType>::DetailedSuccess(const ContentType content) {
  this->content = content;
}

template<typename ContentType>
ContentType DetailedSuccess<ContentType>::getContent() const {
  return this->content;
}

template<typename ContentType>
bool DetailedSuccess<ContentType>::hasContent() const {
  return !std::is_same_v<ContentType, void>;
}

template<typename ContentType>
DetailedSuccess<ContentType> succeed(ContentType content) {
  return DetailedSuccess<ContentType>(content);
}

template<typename ContentType>
inline std::string show(const DetailedSuccess<ContentType>&) {
  return "DetailedSuccess";
}
