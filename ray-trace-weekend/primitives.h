#pragma once

#include "color.h"
#include "vec3.h"
#include "ray.h"

class Primitive {
 public:
  virtual NumType collide_ray(const RayC& ray) const = 0;
  virtual Vec3C get_normal(const Vec3C& at) const = 0;
  virtual ColorC get_color(const Vec3C& at) const = 0;
};

class BackgroundWall: public Primitive {
  Vec3C _position;
  ColorC _color;

 public:
  BackgroundWall(const Vec3C& pos, const ColorC& col);
  virtual NumType collide_ray(const RayC& ray) const;
  virtual Vec3C get_normal(const Vec3C& at) const;
  virtual ColorC get_color(const Vec3C& pos) const;
};

class Sphere : public Primitive {
  Vec3C _position;
  NumType _radius;

  // will need a "material" but color for now
  ColorC _color;
 public:
  Sphere(const Vec3C& pos, NumType r, ColorC c = ColorC());
  virtual NumType collide_ray(const RayC& ray) const;
  virtual Vec3C get_normal(const Vec3C& at) const;
  virtual ColorC get_color(const Vec3C& pos) const;
};
