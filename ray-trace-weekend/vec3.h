#pragma once

#include <cmath>
#include <ostream>

#include "base_numeric.h"

using std::sqrt;

template <typename T>
class Vec3 : public ElementWise<T, Vec3<T>, 3> {
  // T d[3];

 public:
  Vec3() : ElementWise<T, Vec3<T>, 3>(0, 0, 0) {}
  Vec3(T x, T y, T z) : ElementWise<T, Vec3<T>, 3>(x, y, z) {}

  T x() const { return this->d[0]; }
  T y() const { return this->d[1]; }
  T z() const { return this->d[2]; }

  T dot(const Vec3<T>& b) const {
    return (x() * b.x()) + (y() * b.y()) + (z() * b.z());
  }

  T l_squared() const { return dot(*this); }

  T length() const { return sqrt(l_squared()); }

  Vec3<T> cross(const Vec3<T>& b) const {
    return Vec3(y() * b.z() - z() * b.y(), x() * b.z() - z() * b.x(),
                x() * b.y() - y() * b.x());
  }

  Vec3<T> unit() const { return *this / length(); }
};

using Vec3C = Vec3<NumType>;

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vec3<T> v) {
  return out << "(" << v.x() << "," << v.y() << "," << v.z() << ")";
}
