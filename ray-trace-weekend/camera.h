#pragma once

#include "vec3.h"
#include "color.h"
#include "frame.h"

#include <vector>

class Scene;

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

  int scan_scene(const Scene& s, Box size, std::vector<ColorC>& frame) const;
};
