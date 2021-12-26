
#include "primitives.h"

#include <algorithm>
#include <cmath>

Sphere::Sphere(const Vec3C& pos, NumType r, ColorC c)
    : _position(pos), _radius(r), _color(c) {}

NumType Sphere::collide_ray(const RayC& ray) const {
  // Ray has origin + direction
  // We really care about the "t". If we can return t + pos great

  // Sphere has origin + radius
  // (R_o + t*R_d - S_o) dot self = S_radius
  // ((R_o - S_o) + t*R_d) dot self
  // (R_o - S_o)^2 + 2*t*R_d dot (R_o - S_o) + t^2(R_d dot R_d) - S_radius = 0
  // quad formula (-b +/- sqrt(b^2 - 4ac))/2a
  auto ray_to_sphere = ray.origin() - _position;
  auto a = ray.dir().l_squared();
  auto b = 2 * (ray.dir().dot(ray_to_sphere));
  auto c = ray_to_sphere.l_squared() - (_radius * _radius);

  NumType radicand = b * b - (4.0 * a * c);

  if (radicand < 0) {
    return -1;
  }
  auto negT = (-b - std::sqrt(radicand)) / (2 * a);
  auto posT = (-b + std::sqrt(radicand)) / (2 * a);

  if (negT < 0 && posT < 0) {
    return -1;
  } else if (negT < 0) {
    return posT;
  } else if (posT < 0) {
    return negT;
  } else {
    return std::min(negT, posT);
  }
}

Vec3C Sphere::get_normal(const Vec3C& at) const {
  return (at - _position).unit();
}

ColorC Sphere::get_color(const Vec3C& at) const {
  auto n = (get_normal(at)+ Vec3C(1, 1, 1))*0.5;
  return ColorC(n.x(), n.y(), n.z());
  //return _color;
}

BackgroundWall::BackgroundWall(const Vec3C& pos, const ColorC& col)
    : _position(pos), _color(col) {}

NumType BackgroundWall::collide_ray(const RayC& ray) const {
  // ray.origin + t ray.dir = (x, y, _pos.z)
  auto t = (_position.z() - ray.origin().z()) / (ray.dir().z());
  return t;
}
Vec3C BackgroundWall::get_normal(const Vec3C& at) const {
  // The wal is flat vertical
  return Vec3C(0, 0, 1);
}

ColorC BackgroundWall::get_color(const Vec3C& pos) const {
  ColorC gradient_start(1, 1, 1);
  NumType unit_y = (pos - _position).y();
  NumType t = 0.25 * (unit_y + 2.0);
  if (t > 1) {
    return ColorC();
  }
  return gradient_start * (1.0 - t) + _color * t;
}
