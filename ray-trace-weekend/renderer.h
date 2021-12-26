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

 public:
  Renderer(Box size, std::string filename);
  void render(const Scene& s, const Camera& c);

 private:
  void write_ppm(const std::vector<ColorC>& pixels);
};