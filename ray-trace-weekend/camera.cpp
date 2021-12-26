
#include "camera.h"
#include "ray.h"

Camera::Camera(const Vec3C& position,
               NumType view_width,
               NumType view_height,
               NumType focal_length)
    : _position(position) {
  _right_dir = Vec3C(view_width, 0, 0);
  _up_dir = Vec3C(0, view_height, 0);
  _top_left_point =
      _position + Vec3C(0, 0, -focal_length) - _right_dir * 0.5 + _up_dir * 0.5;
}

RayC Camera::get_pixel_ray( NumType x_percent, NumType y_percent) const {
  RayC r(_position, _top_left_point - _up_dir * y_percent +
                      _right_dir * x_percent);
  return r;
}
