#ifndef COMPACKT_MATH_VEC2_H
#define COMPACKT_MATH_VEC2_H

#include <cmath>
#include <ostream>

namespace compackt::math {

/**
 * @brief Two-dimensional vector with arithmetic and length operations.
 *
 * Vec2 is the foundational math primitive of the Compackt engine. It is a
 * value type with no ownership semantics: copying is cheap and assignment is
 * always safe. All arithmetic operators are @c constexpr so the type can be
 * used in compile-time contexts.
 *
 * The class is templated to support multiple scalar types (typically @c float
 * for runtime simulation and @c double for precision-sensitive math). The
 * @c Vec2f alias is provided for the common case.
 *
 * Definitions live in the private @c Vec2.inl include, which is brought in at
 * the bottom of this header. Consumers of the engine cannot include the
 * @c .inl directly.
 *
 * @tparam T Underlying scalar type (e.g. @c float, @c double).
 */
template <typename T>
class Vec2 {
 public:
  T x; ///< Horizontal component.
  T y; ///< Vertical component.

  /**
   * @brief Default constructor. Initializes both components to @c T{} (zero).
   */
  constexpr Vec2();

  /**
   * @brief Construct a vector from explicit components.
   * @param x_in Initial value for @c x.
   * @param y_in Initial value for @c y.
   */
  constexpr Vec2(T x_in, T y_in);

  /**
   * @brief Component-wise addition.
   * @param rhs Right-hand operand.
   * @return A new vector whose components are the pairwise sums.
   */
  constexpr Vec2 operator+(const Vec2& rhs) const;

  /**
   * @brief Component-wise subtraction.
   * @param rhs Right-hand operand.
   * @return A new vector whose components are the pairwise differences.
   */
  constexpr Vec2 operator-(const Vec2& rhs) const;

  /**
   * @brief Scalar multiplication (vector on the left).
   * @param scalar Scalar to multiply each component by.
   * @return A new vector with both components scaled.
   */
  constexpr Vec2 operator*(T scalar) const;

  /**
   * @brief Component-wise compound addition.
   * @param rhs Right-hand operand.
   * @return Reference to @c *this after mutation.
   */
  constexpr Vec2& operator+=(const Vec2& rhs);

  /**
   * @brief Exact component-wise equality.
   * @param rhs Right-hand operand.
   * @return @c true if both components compare equal.
   */
  constexpr bool operator==(const Vec2& rhs) const;

  /**
   * @brief Squared length of the vector.
   *
   * Prefer this over @c Length() whenever the actual length is not needed
   * (for example when comparing distances), since it avoids a square root.
   *
   * @return @c x*x + y*y.
   */
  [[nodiscard]] T LengthSquared() const;

  /**
   * @brief Euclidean length of the vector.
   * @return @c sqrt(x*x + y*y).
   */
  [[nodiscard]] T Length() const;
};

/**
 * @brief Scalar multiplication (scalar on the left).
 *
 * Free-function overload that makes @c 2.0f * v read symmetrically with
 * @c v * 2.0f.
 *
 * @tparam T Underlying scalar type.
 * @param scalar Scalar multiplier.
 * @param v Vector to scale.
 * @return A new vector with both components scaled.
 */
template <typename T>
constexpr Vec2<T> operator*(T scalar, const Vec2<T>& v);

/**
 * @brief Stream insertion for human-readable output.
 *
 * Writes the vector in the form @c "(x, y)".
 *
 * @tparam T Underlying scalar type.
 * @param os Destination stream.
 * @param v Vector to format.
 * @return Reference to @p os for chaining.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vec2<T>& v);

/**
 * @brief Convenience alias for the common single-precision case.
 */
using Vec2f = Vec2<float>;

}  // namespace compackt::math

// Template definitions live in Vec2.inl, next to this header. A template's
// body must be visible at every instantiation site, so the .inl ships as part
// of the public include tree alongside Vec2.h.
#include "Vec2.inl"

#endif  // COMPACKT_MATH_VEC2_H
