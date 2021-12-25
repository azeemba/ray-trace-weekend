#pragma once

#include "color.h"
#include "ray.h"

class Scene {
  // store representation somehow

  ColorC hit_background(const RayC& ray) const;

 public:
  ColorC fire_ray(const RayC& ray) const;
};


