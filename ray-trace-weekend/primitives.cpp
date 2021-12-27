
#include "primitives.h"

#include <algorithm>
#include <cmath>

std::shared_ptr<const Material> Primitive::get_material(const Vec3C& at) {
  return _material;
}

Sphere::Sphere(const Vec3C& pos,
               NumType r,
               std::shared_ptr<const Material> material)
    : _position(pos), _radius(r) {
  _material = material;
}

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

BackgroundWall::BackgroundWall(const Vec3C& pos,
                               std::shared_ptr<const Material> material)
    : _position(pos) {
  _material = material;
}

NumType BackgroundWall::collide_ray(const RayC& ray) const {
  // ray.origin + t ray.dir = (x, y, _pos.z)
  auto t = (_position.z() - ray.origin().z()) / (ray.dir().z());
  return t;
}
Vec3C BackgroundWall::get_normal(const Vec3C& at) const {
  // The wal is flat vertical
  return Vec3C(0, 0, 1);
}
