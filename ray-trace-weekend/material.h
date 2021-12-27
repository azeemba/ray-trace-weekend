#pragma once

#include "color.h"
#include "ray.h"
#include "vec3.h"

class Primitive;
class Scene;

struct RayCollision {
  RayC ray;
  Vec3C location;
  Vec3C normal_unit;
  size_t depth;
};

class Material {
 public:
  virtual ColorC get_color(const RayCollision& collision,
                           const Primitive& primitive,
                           const Scene& scene) const = 0;
};

class NormalMaterial : public Material {

  virtual ColorC get_color(const RayCollision& collision,
                           const Primitive& primitive,
                           const Scene& scene) const;
};

class DiffuseMaterial : public Material {
  ColorC _color;

 public:
  virtual ColorC get_color(const RayCollision& collision,
                           const Primitive& primitive,
                           const Scene& scene) const;
};

class GradientMaterial : public Material {
  ColorC _gradient_start;
  ColorC _gradient_end;

 public:
  GradientMaterial(const ColorC& start, const ColorC& end);
  virtual ColorC get_color(const RayCollision& collision,
                           const Primitive& primitive,
                           const Scene& scene) const;
};
