
#include "scene.h"
#include "material.h"
#include <algorithm>

ColorC Scene::hit_background(const RayC& ray) const {
  ColorC gradient_start(1, 1, 1);
  ColorC gradient_end(0.5, 0.7, 1.0);
  NumType unit_y = ray.dir().unit().y();
  NumType t = 0.5 * (unit_y + 1.0);
  return gradient_start * (1.0 - t) + gradient_end * t;
}

size_t Scene::set_max_depth(size_t depth) {
  _max_depth = depth;
  return _max_depth;
}

size_t Scene::take_object(std::unique_ptr<Primitive> obj) {
  _objects.push_back(std::move(obj));
  return _objects.size() - 1;
}

ColorC Scene::fire_ray(const RayC& ray, size_t depth) const {
  if (_objects.empty())
    return ColorC();
  if (depth > _max_depth) {
    return ColorC();
  }

  Primitive* smallest = _objects.begin()->get();
  NumType smallest_t = INFINITY;
  for (auto& obj : _objects) {
    auto t = obj->collide_ray(ray);
    if (t > 0 && t < smallest_t) {
      smallest_t = t;
      smallest = obj.get();
    }
  }
  auto location = ray.at(smallest_t);
  RayCollision collision{ray, location, smallest->get_normal(location), depth+1};
  return smallest->get_material(ray.at(smallest_t))->get_color(collision, *smallest, *this);
}
