// Private template definitions for Vec2.
//
// This file has no include guard of its own — the parent header's guard
// (COMPACKT_MATH_VEC2_H) covers it. It must not be included directly; it is
// brought in at the bottom of <compackt/math/Vec2.h>.
//
// It lives under engine/src/ on the engine's PRIVATE include path so that
// consumers of compackt_engine cannot reach it via #include.

namespace compackt::math {

template <Numeric T>
constexpr Vec2<T>::Vec2() : x{T{}}, y{T{}} {}

template <Numeric T>
constexpr Vec2<T>::Vec2(T x_in, T y_in) : x{x_in}, y{y_in} {}

template <Numeric T>
constexpr Vec2<T> Vec2<T>::operator+(const Vec2& rhs) const {
  return {x + rhs.x, y + rhs.y};
}

template <Numeric T>
constexpr Vec2<T> Vec2<T>::operator-(const Vec2& rhs) const {
  return {x - rhs.x, y - rhs.y};
}

template <Numeric T>
constexpr Vec2<T> Vec2<T>::operator*(T scalar) const {
  return {x * scalar, y * scalar};
}

template <Numeric T>
constexpr Vec2<T>& Vec2<T>::operator+=(const Vec2& rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

template <Numeric T>
constexpr bool Vec2<T>::operator==(const Vec2& rhs) const {
  return x == rhs.x && y == rhs.y;
}

template <Numeric T>
T Vec2<T>::LengthSquared() const {
  return x * x + y * y;
}

template <Numeric T>
T Vec2<T>::Length() const {
  return std::sqrt(LengthSquared());
}

template <Numeric T>
constexpr Vec2<T> operator*(T scalar, const Vec2<T>& v) {
  return v * scalar;
}

template <Numeric T>
std::ostream& operator<<(std::ostream& os, const Vec2<T>& v) {
  return os << "(" << v.x << ", " << v.y << ")";
}

}  // namespace compackt::math
