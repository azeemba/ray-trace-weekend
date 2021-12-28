#pragma once

#include "frame.h"
#include "color.h"
#include <string>
#include <vector>

class Scene;
class Camera;

class Renderer {
  Box _box;
  std::string _filename;
  size_t _samples;

 public:
  Renderer(Box size, std::string filename, size_t samples=1);
  void render(const Scene& s, const Camera& c, bool save=true);

 private:
  void write_ppm(const std::vector<ColorC>& pixels);
  void display_frame(const std::vector<ColorC>& pixels);
  ColorC average_pixel(const Scene&s, const Camera& c, Loc pixel);
};
