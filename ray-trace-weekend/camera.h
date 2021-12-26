#pragma once

#include "vec3.h"
#include "ray.h"

class Camera {
  Vec3C _position;
  Vec3C _right_dir;
  Vec3C _up_dir;
  Vec3C _top_left_point;

 public:
  Camera(const Vec3C& position,
         NumType view_width,
         NumType view_height,
         NumType focal_length);

  RayC get_pixel_ray(NumType x_percent, NumType y_percent) const;
};
