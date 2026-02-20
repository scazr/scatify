#include <variant>


template<typename A>
class Just {
private:
  A value;
public:
  Just(A value) : value(value) {}
  A getValue() const { return value; }
};

class Nothing {};

template<typename A>
using Maybe = std::variant<Just<A>, Nothing>;
