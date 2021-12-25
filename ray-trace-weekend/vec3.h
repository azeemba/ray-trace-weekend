#pragma once

#include <cmath>

using std::sqrt;

template <typename T, typename Self, int N>
class ElementWise {
 protected:
  T d[N];

 public:
  ElementWise() : d{0, 0, 0} {}
  ElementWise(T a, T b, T c) : d{a, b, c} {}
  T operator[](size_t i) const { return d[i]; }
  T& operator[](size_t i) { return d[i]; }

  Self operator*(const Self& b) const {
    return Self(d[0] * b[0], d[1] * b[1], d[2] * b[2]);
  }

  Self operator*(const T scalar) const {
    return Self(scalar * d[0], scalar * d[1], scalar * d[2]);
  }

  Self operator-() const { return *this * -1; }

  Self operator+(const Self& b) const {
    return Self(d[0] + b[0], d[1] + b[1], d[2] + b[2]);
  }

  Self operator-(const Self& b) const { return *this + (-b); }
};

template <typename T>
class Vec3 : public ElementWise<T, Vec3<T>, 3> {
  // T d[3];

 public:
  Vec3() : ElementWise{0, 0, 0} {}
  Vec3(T x, T y, T z) : ElementWise{x, y, z} {}

  T x() const { return d[0]; }
  T y() const { return d[1]; }
  T z() const { return d[2]; }

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
