
#include "scene.h"
#include <algorithm>

ColorC Scene::hit_background(const RayC& ray) const {
  ColorC gradient_start(1, 1, 1);
  ColorC gradient_end(0.5, 0.7, 1.0);
  NumType unit_y = ray.dir().unit().y();
  NumType t = 0.5 * (unit_y + 1.0);
  return gradient_start * (1.0 - t) + gradient_end * t;
}

size_t Scene::take_object(std::unique_ptr<Primitive> obj) {
  _objects.push_back(std::move(obj));
  return _objects.size() - 1;
}

ColorC Scene::fire_ray(const RayC& ray) const {
  if (_objects.empty())
    return ColorC();

  Primitive* smallest = _objects.begin()->get();
  NumType smallest_t = INFINITY;
  for (auto& obj : _objects) {
    auto t = obj->collide_ray(ray);
    if (t > 0 && t < smallest_t) {
      smallest_t = t;
      smallest = obj.get();
    }
  }

  return smallest->get_color(ray.at(smallest_t));
}
