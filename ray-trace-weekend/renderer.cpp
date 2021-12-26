
#include "renderer.h"
#include "camera.h"
#include "frame.h"
#include "scene.h"

#include <cassert>
#include <fstream>
#include <iostream>

Renderer::Renderer(Box size, std::string filename)
    : _box(size), _filename(filename) {}
void Renderer::render(const Scene& s, const Camera& c) {
  auto frame = initialize_frame(_box);
  c.scan_scene(s, _box, frame);
  write_ppm(frame);
}

void Renderer::write_ppm(const std::vector<ColorC>& pixels) {
  assert(pixels.size() >= _box.width * _box.height);
  std::ofstream file(_filename);

  file << "P3\n" << _box.width << " " << _box.height << "\n255\n";
  for (size_t row = 0; row < _box.height; ++row) {
    std::cerr << "\rScanlines remaining: " << row << ' ' << std::flush;
    for (size_t col = 0; col < _box.width; ++col) {
      size_t index = to_index(row, col, _box);
      const auto& p = pixels[index];
      p.write_ppm(file);
    }
  }
  file.close();
  std::cerr << "Donezo\n";
}
