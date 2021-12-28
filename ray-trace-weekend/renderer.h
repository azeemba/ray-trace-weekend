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
  void render(const Scene& s, const Camera& c, bool save=true, size_t samples=1);

  void play_animation(Scene& s, Camera& c);

 private:
  std::vector<ColorC> render_frame(const Scene& s, const Camera& c, size_t samples);
  void write_ppm(const std::vector<ColorC>& pixels);
  void display_frame(const std::vector<ColorC>& pixels);
  ColorC average_pixel(const Scene&s, const Camera& c, Loc pixel, size_t samples);
};
