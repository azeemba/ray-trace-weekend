#pragma once

#include "vec3.h"

template <typename T>
class Color : Vec3<T> {
 public:
  using Vec3::Vec3;

  T r() const { return x(); }
  T g() const { return y(); }
  T b() const { return z(); }

  std::ostream& write(std::ostream& file) const {
    int ir = static_cast<int>(255.999 * r());
    int ig = static_cast<int>(255.999 * g());
    int ib = static_cast<int>(255.999 * b());

    return file << ir << " " << ig << " " << ib << "\n";
  }
};