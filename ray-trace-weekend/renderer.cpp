
#include "renderer.h"
#include "camera.h"
#include "frame.h"
#include "scene.h"
#include "random_helper.h"

#include <algorithm>
#include <cassert>
#include <execution>
#include <fstream>
#include <iostream>
#include <numeric>


// Anon namespace

namespace {

};  // namespace

Renderer::Renderer(Box size, std::string filename, size_t samples)
    : _box(size), _filename(filename), _samples(samples) {}

ColorC Renderer::average_pixel(const Scene& s, const Camera& c, Loc pixel) {
  ColorC total_color;
  for (size_t i = 0; i < _samples; ++i) {
    NumType x_factor = (NumType(pixel.col) + get_uniform_random(-0.5, 0.5))/ _box.width;
    NumType y_factor = (NumType(pixel.row) + get_uniform_random(-0.5, 0.5))/ _box.height;
    auto r = c.get_pixel_ray(x_factor, y_factor);
    total_color = total_color + s.fire_ray(r);
  }
  total_color = total_color / _samples;
  total_color.gamma_correct(2);
  return total_color;
}

void Renderer::render(const Scene& s, const Camera& c, bool save) {
  auto frame = initialize_frame(_box);

  std::vector<size_t> indices(_box.height * _box.width);
  // could use iota views which saves the allocation but C++20, do we want it?
  iota(indices.begin(), indices.end(), 0);

  transform(std::execution::par_unseq, indices.begin(), indices.end(),
            frame.begin(), [this, &s, &c](size_t index) {
              Loc l = to_loc(index, _box);
              return average_pixel(s, c, l);
            });

  if (save) write_ppm(frame);
}

void Renderer::write_ppm(const std::vector<ColorC>& pixels) {
  assert(pixels.size() >= _box.width * _box.height);
  std::ofstream file(_filename);

  file << "P3\n" << _box.width << " " << _box.height << "\n255\n";
  for (size_t row = 0; row < _box.height; ++row) {
    for (size_t col = 0; col < _box.width; ++col) {
      size_t index = to_index(row, col, _box);
      const auto& p = pixels[index];
      p.write_ppm(file);
    }
  }
  file.close();
}
