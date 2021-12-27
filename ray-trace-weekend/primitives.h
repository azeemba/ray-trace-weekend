#pragma once

#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <memory>

class Material;

class Primitive {
 protected:
  std::shared_ptr<const Material> _material;
 public:
  virtual NumType collide_ray(const RayC& ray) const = 0;
  virtual Vec3C get_normal(const Vec3C& at) const = 0;

  // override for objects that have multiple materials
  virtual std::shared_ptr<const Material> get_material(const Vec3C& at);
};

class BackgroundWall: public Primitive {
  Vec3C _position;

 public:
  BackgroundWall(const Vec3C& pos, std::shared_ptr<const Material> material);
  virtual NumType collide_ray(const RayC& ray) const;
  virtual Vec3C get_normal(const Vec3C& at) const;
};

class Sphere : public Primitive {
  Vec3C _position;
  NumType _radius;

 public:
  Sphere(const Vec3C& pos, NumType r, std::shared_ptr<const Material> material);
  virtual NumType collide_ray(const RayC& ray) const;
  virtual Vec3C get_normal(const Vec3C& at) const;
};
