#pragma once

#include "color.h"
#include "primitives.h"
#include "ray.h"

#include <vector>

class Scene {
  std::vector<std::unique_ptr<Primitive>> _objects;
  size_t _max_depth;

  ColorC hit_background(const RayC& ray) const;

 public:
  Scene() : _max_depth(1) {}
  size_t take_object(std::unique_ptr<Primitive> obj);
  size_t set_max_depth(size_t);
  ColorC fire_ray(const RayC& ray, size_t cur_depth = 0) const;
};
