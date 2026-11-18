#ifndef COMPACKT_MATH_MAT4_H
#define COMPACKT_MATH_MAT4_H

#include <cmath>

#include "Numeric.h"
#include "Vec2.h"
#include "Vec3.h"

namespace compackt::math {

template <Numeric T>
class Mat4 {
 public:
  T data[16];

  constexpr Mat4();

  constexpr Mat4 operator*(const Mat4& rhs) const;
  constexpr Mat4& operator*=(const Mat4& rhs);
  constexpr bool operator==(const Mat4& rhs) const;

  constexpr Mat4 Transposed() const;

  static constexpr Mat4 Identity();
  static constexpr Mat4 Translate(const Vec2<T>& offset);
  static constexpr Mat4 Translate(const Vec3<T>& offset);
  static Mat4 RotateZ(T radians);
  static constexpr Mat4 Scale(const Vec2<T>& factors);
  static constexpr Mat4 Scale(const Vec3<T>& factors);
  static constexpr Mat4 Ortho(T left, T right, T bottom, T top,
                              T near, T far);
};

using Mat4f = Mat4<float>;

}  // namespace compackt::math

#include "Mat4.inl"

#endif  // COMPACKT_MATH_MAT4_H
