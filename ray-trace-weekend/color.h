#pragma once

#include "vec3.h"

template <typename T>
class Color: public ElementWise<T, Color<T>, 3> {
 public:
  Color() : ElementWise{0, 0, 0} {}
  Color(T r, T g, T b) : ElementWise{r, g, b} {}

  T r() const { return d[0]; }
  T g() const { return d[1]; }
  T b() const { return d[2]; }

  std::ostream& write_ppm(std::ostream& file) const {
    int ir = static_cast<int>(255.999 * r());
    int ig = static_cast<int>(255.999 * g());
    int ib = static_cast<int>(255.999 * b());

    return file << ir << " " << ig << " " << ib << "\n";
  }
};