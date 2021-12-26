
#include "camera.h"
#include "ray.h"
#include "scene.h"

#include <algorithm>
#include <execution>
#include <numeric>

Camera::Camera(const Vec3C& position,
               NumType view_width,
               NumType view_height,
               NumType focal_length)
    : _position(position) {
  _right_dir = Vec3C(view_width, 0, 0);
  _up_dir = Vec3C(0, view_height, 0);
  _lower_left_point =
      _position + Vec3C(0, 0, -focal_length) - _right_dir * 0.5 - _up_dir * 0.5;
}

int Camera::scan_scene(const Scene& s,
                       Box size,
                       std::vector<ColorC>& frame) const {
  std::vector<size_t> indices(size.height * size.width);
  iota(indices.begin(), indices.end(), 0);

  transform(std::execution::par_unseq, indices.begin(), indices.end(),
            frame.begin(), [&size, this, &s](size_t index) {
              Loc l = to_loc(index, size);
              NumType x_factor = NumType(l.col) / size.width;
              NumType y_factor = NumType(l.row) / size.height;
              RayC r(_position, _lower_left_point + _up_dir * y_factor +
                                    _right_dir * x_factor);
              return s.fire_ray(r);
            });
  return 0;
}