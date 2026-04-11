#pragma once
#include "Success.hpp"

template<typename ContentType>
class DetailedSuccess : public Success {
  ContentType content;
public:
  DetailedSuccess(const ContentType content);
  ContentType getContent() const;
  bool hasContent() const;
};

#include "DetailedSuccess.tpp"
