#pragma once

#include <algorithm>
#include "vec3.h"

template <typename T>
class Color : public ElementWise<T, Color<T>, 3> {
 private:
   uint8_t to_256(size_t i) const {
    return static_cast<uint8_t>(255.999 * std::clamp<T>(this->d[i], 0, 1));
  }

 public:
  Color() : ElementWise<T, Color<T>, 3>(0, 0, 0) {}
  Color(T r, T g, T b) : ElementWise<T, Color<T>, 3>(r, g, b) {}

  T r() const { return this->d[0]; }
  T g() const { return this->d[1]; }
  T b() const { return this->d[2]; }

  uint8_t ir() const { return to_256(0); }
  uint8_t ig() const { return to_256(1); }
  uint8_t ib() const { return to_256(2); }

 void gamma_correct(int val = 2) {
    if (val == 2) {
      this->d[0] = std::sqrt(this->d[0]);
      this->d[1] = std::sqrt(this->d[1]);
      this->d[2] = std::sqrt(this->d[2]);
    } else {
      this->d[0] = std::pow(this->d[0], 1.0 / val);
      this->d[1] = std::pow(this->d[1], 1.0 / val);
      this->d[2] = std::pow(this->d[2], 1.0 / val);
    }
  }

  std::ostream& write_ppm(std::ostream& file) const {
    return file << (int)ir() << " " << (int)ig() << " " << (int)ib() << "\n";
  }
};
using ColorC = Color<NumType>;
