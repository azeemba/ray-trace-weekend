#pragma once

#include "color.h"
#include "ray.h"
#include "primitives.h"

#include <vector>

class Scene {
  // store representation somehow
  std::vector<std::unique_ptr<Primitive>> _objects;

  ColorC hit_background(const RayC& ray) const;

 public:
  size_t take_object(std::unique_ptr<Primitive> obj);
  ColorC fire_ray(const RayC& ray) const;
};


