#include <variant>

template<typename L, typename R>
class Either {
public:
  std::variant<L, R> data;
  
  Either(const L l) : data(l) {}
  Either(const R r) : data(r) {}

  bool isLeft() const { return std::holds_alternative<L>(data); }
  bool isRight() const { return std::holds_alternative<R>(data); }

  template<typename F>
  F fmap(F func) const {
    if(isRight()) {

    }
  }
 
};
