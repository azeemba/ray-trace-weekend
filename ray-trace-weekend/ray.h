#pragma once

#include "vec3.h"

template <typename T>
class Ray {
  Vec3<T> _origin;
  Vec3<T> _dir;

 public:
  Ray(const Vec3<T>& o, const Vec3<T>& d) : _origin(o), _dir(d) {}

  Vec3<T> origin() const { return _origin; }
  Vec3<T> dir() const { return _dir; }

  Vec3<T> at(T t) { return _origin + _dir * t; }
};

using RayC = Ray<NumType>;
