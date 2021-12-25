
#include "scene.h"

ColorC Scene::hit_background(const RayC& ray) const {
  ColorC gradient_start(1, 1, 1);
  ColorC gradient_end(0.5, 0.7, 1.0);
  NumType unit_y = ray.dir().unit().y();
  NumType t = 0.5 * (unit_y + 1.0);
  return gradient_start * (1.0 - t) + gradient_end * t;
}

ColorC Scene::fire_ray(const RayC& ray) const {
  // check if incident on any objects.
  // if not, delegate to background
  return hit_background(ray);
}
