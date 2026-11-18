#ifndef COMPACKT_MATH_TRANSFORM2D_H
#define COMPACKT_MATH_TRANSFORM2D_H

#include "Mat4.h"
#include "Vec2.h"

namespace compackt::math {

struct Transform2D {
  Vec2f position{0.0f, 0.0f};
  Vec2f scale{1.0f, 1.0f};
  float rotation{0.0f};

  Mat4f ToMatrix() const {
    return Mat4f::Translate(position)
         * Mat4f::RotateZ(rotation)
         * Mat4f::Scale(scale);
  }
};

}  // namespace compackt::math

#endif  // COMPACKT_MATH_TRANSFORM2D_H
