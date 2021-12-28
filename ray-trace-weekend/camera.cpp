
#include "camera.h"
#include "ray.h"

#include <cmath>

Camera::Camera(const Vec3C& position,
               NumType view_width,
               NumType view_height,
               NumType focal_length)
    : _position(position) {
  NumType vertical_field_of_view = PI/3.0;
  NumType scale_vertical = 2*std::tan(vertical_field_of_view / 2.0);
  NumType scale_horizontal = scale_vertical * view_width / view_height;

  _right_dir = Vec3C(view_width*scale_horizontal, 0, 0);
  _up_dir = Vec3C(0, view_height*scale_vertical, 0);
  _top_left_point =
      _position + Vec3C(0, 0, -focal_length) - _right_dir * 0.5 + _up_dir * 0.5;
}

void Camera::recompute_orientation(const Vec3C& position, const Vec3C& lookat, NumType focal_length) {
  _position = position;
  auto forward = (lookat - _position).unit();
  auto right_unit = forward.cross(Vec3C(0, 1, 0)).unit();
  auto up_unit = forward.cross(right_unit).unit();

  _right_dir = right_unit * (_right_dir.length());
  _up_dir = up_unit * (_up_dir.length());

  _top_left_point =
      _position + forward*focal_length - _right_dir * 0.5 + _up_dir * 0.5;
}

RayC Camera::get_pixel_ray( NumType x_percent, NumType y_percent) const {
  RayC r(_position, _top_left_point - _up_dir * y_percent +
                      _right_dir * x_percent);
  return r;
}
