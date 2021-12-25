#pragma once

#include <cmath>

using std::sqrt;

template <typename T>
class Vec3 {
  T d[3];

 public:
  Vec3() : d{0, 0, 0} {}
  Vec3(T x, T y, T z) : d{x, y, z} {}

  T x() const { return d[0]; }
  T y() const { return d[1]; }
  T z() const { return d[2]; }

  // indexing
  T operator[](size_t i) const { return d[i]; }
  T& operator[](size_t i) { return d[i]; }

  Vec3<T> operator*(const Vec3<T>& b) const {
    return Vec3(x() * b.x(), y() * b.y(), z() * b.z());
  }

  Vec3<T> operator*(const T scalar) const {
    return Vec3(scalar * x(), scalar * y(), scalar * z());
  }

  Vec3<T> operator-() const { return *this * -1; }

  Vec3<T> operator+(const Vec3<T>& b) const {
    return Vec3(x() + b.x(), y() + b.y(), z() + b.z());
  }

  T dot(const Vec3<T>& b) const {
    return x() * b.x() + y() * b.y() + z() * b.z();
  }

  T l_squared() const { return dot(*this); }

  T length() const { return sqrt(l_squared()); }

  Vec3<T> cross(const Vec3<T>& b) const {
    return Vec3(y() * b.z() - z() * b.y(), x() * b.z() - z() * b.x(),
                x() * b.y() - y() * b.x());
  }

  Vec3<T> unit() const { return *this * (1 / length()); }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vec3<T> v) {
  return out << "(" << v.x() << "," << v.y() << "," << v.z() << ")";
}
