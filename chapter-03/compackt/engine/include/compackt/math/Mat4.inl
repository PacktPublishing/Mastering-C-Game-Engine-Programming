namespace compackt::math {

// Default constructor produces an identity matrix.
template <Numeric T>
constexpr Mat4<T>::Mat4()
    : data{T{1}, T{},  T{},  T{},
           T{},  T{1}, T{},  T{},
           T{},  T{},  T{1}, T{},
           T{},  T{},  T{},  T{1}} {}

template <Numeric T>
constexpr Mat4<T> Mat4<T>::operator*(const Mat4& rhs) const {
  Mat4 result;
  for (int col = 0; col < 4; ++col) {
    for (int row = 0; row < 4; ++row) {
      T sum = T{};
      for (int k = 0; k < 4; ++k) {
        sum += data[k * 4 + row] * rhs.data[col * 4 + k];
      }
      result.data[col * 4 + row] = sum;
    }
  }
  return result;
}

template <Numeric T>
constexpr Mat4<T>& Mat4<T>::operator*=(const Mat4& rhs) {
  *this = *this * rhs;
  return *this;
}

template <Numeric T>
constexpr bool Mat4<T>::operator==(const Mat4& rhs) const {
  for (int i = 0; i < 16; ++i) {
    if (data[i] != rhs.data[i]) return false;
  }
  return true;
}

template <Numeric T>
constexpr Mat4<T> Mat4<T>::Transposed() const {
  Mat4 result;
  for (int col = 0; col < 4; ++col) {
    for (int row = 0; row < 4; ++row) {
      result.data[col * 4 + row] = data[row * 4 + col];
    }
  }
  return result;
}

template <Numeric T>
constexpr Mat4<T> Mat4<T>::Identity() {
  return Mat4{};
}

template <Numeric T>
constexpr Mat4<T> Mat4<T>::Translate(const Vec2<T>& offset) {
  Mat4 m;
  m.data[12] = offset.x;
  m.data[13] = offset.y;
  return m;
}

template <Numeric T>
constexpr Mat4<T> Mat4<T>::Translate(const Vec3<T>& offset) {
  Mat4 m;
  m.data[12] = offset.x;
  m.data[13] = offset.y;
  m.data[14] = offset.z;
  return m;
}

// We are not compiling with C++26 in chapter 3
// so std::cos and std::sin cannot be constexpr
template <Numeric T>
Mat4<T> Mat4<T>::RotateZ(T radians) {
  T c = std::cos(radians);
  T s = std::sin(radians);
  Mat4 m;
  m.data[0] = c;
  m.data[1] = s;
  m.data[4] = -s;
  m.data[5] = c;
  return m;
}

template <Numeric T>
constexpr Mat4<T> Mat4<T>::Scale(const Vec2<T>& factors) {
  Mat4 m;
  m.data[0] = factors.x;
  m.data[5] = factors.y;
  return m;
}

template <Numeric T>
constexpr Mat4<T> Mat4<T>::Scale(const Vec3<T>& factors) {
  Mat4 m;
  m.data[0] = factors.x;
  m.data[5] = factors.y;
  m.data[10] = factors.z;
  return m;
}

template <Numeric T>
constexpr Mat4<T> Mat4<T>::Ortho(T left, T right, T bottom, T top,
                                 T near, T far) {
  Mat4 m;
  m.data[0]  = T{2} / (right - left);
  m.data[5]  = T{2} / (top - bottom);
  m.data[10] = T{-2} / (far - near);
  m.data[12] = -(right + left) / (right - left);
  m.data[13] = -(top + bottom) / (top - bottom);
  m.data[14] = -(far + near) / (far - near);
  return m;
}

}  // namespace compackt::math
