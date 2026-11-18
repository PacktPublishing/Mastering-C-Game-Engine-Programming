#ifndef COMPACKT_MATH_NUMERIC_H
#define COMPACKT_MATH_NUMERIC_H

#include <type_traits>

namespace compackt::math {

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

}  // namespace compackt::math

#endif  // COMPACKT_MATH_NUMERIC_H
