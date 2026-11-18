namespace compackt::math {

template <Numeric T>
constexpr Vec3<T>::Vec3() : x{T{}}, y{T{}}, z{T{}} {}

template <Numeric T>
constexpr Vec3<T>::Vec3(T x_in, T y_in, T z_in) : x{x_in}, y{y_in}, z{z_in} {}

template <Numeric T>
constexpr Vec3<T> Vec3<T>::operator+(const Vec3& rhs) const {
  return {x + rhs.x, y + rhs.y, z + rhs.z};
}

template <Numeric T>
constexpr Vec3<T> Vec3<T>::operator-(const Vec3& rhs) const {
  return {x - rhs.x, y - rhs.y, z - rhs.z};
}

template <Numeric T>
constexpr Vec3<T> Vec3<T>::operator*(T scalar) const {
  return {x * scalar, y * scalar, z * scalar};
}

template <Numeric T>
constexpr Vec3<T>& Vec3<T>::operator+=(const Vec3& rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}

template <Numeric T>
constexpr bool Vec3<T>::operator==(const Vec3& rhs) const {
  return x == rhs.x && y == rhs.y && z == rhs.z;
}

template <Numeric T>
T Vec3<T>::LengthSquared() const {
  return x * x + y * y + z * z;
}

template <Numeric T>
T Vec3<T>::Length() const {
  return std::sqrt(LengthSquared());
}

template <Numeric T>
constexpr T Vec3<T>::Dot(const Vec3& rhs) const {
  return x * rhs.x + y * rhs.y + z * rhs.z;
}

template <Numeric T>
constexpr Vec3<T> Vec3<T>::Cross(const Vec3& rhs) const {
  return {y * rhs.z - z * rhs.y,
          z * rhs.x - x * rhs.z,
          x * rhs.y - y * rhs.x};
}

template <Numeric T>
constexpr Vec3<T> operator*(T scalar, const Vec3<T>& v) {
  return v * scalar;
}

template <Numeric T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& v) {
  return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

}  // namespace compackt::math
