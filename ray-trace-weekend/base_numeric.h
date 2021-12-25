#pragma once

using NumType = float;

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
