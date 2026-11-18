#ifndef COMPACKT_MATH_VEC3_H
#define COMPACKT_MATH_VEC3_H

#include <cmath>
#include <ostream>

#include "Numeric.h"

namespace compackt::math {

// Solution to Chapter 2 challenge.
template <Numeric T>
class Vec3 {
 public:
  T x;
  T y;
  T z;

  constexpr Vec3();
  constexpr Vec3(T x_in, T y_in, T z_in);

  constexpr Vec3 operator+(const Vec3& rhs) const;
  constexpr Vec3 operator-(const Vec3& rhs) const;
  constexpr Vec3 operator*(T scalar) const;
  constexpr Vec3& operator+=(const Vec3& rhs);
  constexpr bool operator==(const Vec3& rhs) const;

  [[nodiscard]] T LengthSquared() const;
  [[nodiscard]] T Length() const;

  [[nodiscard]] constexpr T Dot(const Vec3& rhs) const;
  [[nodiscard]] constexpr Vec3 Cross(const Vec3& rhs) const;
};

template <Numeric T>
constexpr Vec3<T> operator*(T scalar, const Vec3<T>& v);

template <Numeric T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& v);

using Vec3f = Vec3<float>;

}  // namespace compackt::math

#include "Vec3.inl"

#endif  // COMPACKT_MATH_VEC3_H
