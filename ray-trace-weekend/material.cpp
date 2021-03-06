
#include "material.h"
#include <algorithm>
#include "random_helper.h"
#include "ray.h"
#include "scene.h"

namespace {
Vec3C get_random_vec() {
  return Vec3C(get_uniform_random(-1, 1), get_uniform_random(-1, 1),
               get_uniform_random(-1, 1))
      .unit();
}
}  // namespace

ColorC NormalMaterial::get_color(const RayCollision& collision,
                                 const Primitive& primitive,
                                 const Scene& scene) const {
  auto n = (collision.normal_unit + Vec3C(1, 1, 1)) * 0.5;
  return ColorC(n.x(), n.y(), n.z());
}

ColorC DiffuseMaterial::get_color(const RayCollision& collision,
                                  const Primitive& primitive,
                                  const Scene& scene) const {
  auto out_sphere_center = collision.location + collision.normal_unit;
  auto random_unit = get_random_vec();
  if (random_unit.dot(collision.normal_unit) < 0) {
    random_unit = -random_unit;
  }
  return scene.fire_ray(
             RayC(collision.location, collision.normal_unit + random_unit),
             collision.depth) *
         _color;
}

ColorC MetalMaterial::get_color(const RayCollision& collision,
                                const Primitive& primitive,
                                const Scene& scene) const {
  auto& in_ray = collision.ray.dir();
  auto& n = collision.normal_unit;
  auto reflected_ray =
      n * in_ray.dot(n) * 2 - in_ray + get_random_vec() * _fuzz_factor;

  return scene.fire_ray(RayC(collision.location, -reflected_ray),
                        collision.depth) *
         _color;
}

GradientMaterial::GradientMaterial(const ColorC& start, const ColorC& end)
    : _gradient_start(start), _gradient_end(end) {}

ColorC GradientMaterial::get_color(const RayCollision& collision,
                                   const Primitive& primitive,
                                   const Scene& scene) const {
  NumType unit_y = -collision.location.y();
  NumType t = 0.25 * (unit_y + 2.0);  // should store scaling factors
  t = std::clamp<NumType>(t, 0, 1);
  return _gradient_start * (1.0 - t) + _gradient_end * t;
}
