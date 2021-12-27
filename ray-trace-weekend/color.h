#pragma once

#include "vec3.h"
#include <algorithm>

template <typename T>
class Color: public ElementWise<T, Color<T>, 3> {
 public:
  Color() : ElementWise{0, 0, 0} {}
  Color(T r, T g, T b) : ElementWise{r, g, b} {}

  T r() const { return d[0]; }
  T g() const { return d[1]; }
  T b() const { return d[2]; }

  void gamma_correct(int val=2) {
    if (val == 2) {
      d[0] = std::sqrt(d[0]);
      d[1] = std::sqrt(d[1]);
      d[2] = std::sqrt(d[2]);
    } else {
      d[0] = std::pow(d[0], 1.0 / val);
      d[1] = std::pow(d[1], 1.0 / val);
      d[2] = std::pow(d[2], 1.0 / val);
    }
  }

  std::ostream& write_ppm(std::ostream& file) const {
    int ir = static_cast<int>(255.999 * std::clamp<T>(r(), 0, 1));
    int ig = static_cast<int>(255.999 * std::clamp<T>(g(), 0, 1));
    int ib = static_cast<int>(255.999 * std::clamp<T>(b(), 0, 1));

    return file << ir << " " << ig << " " << ib << "\n";
  }
};
using ColorC = Color<NumType>;

