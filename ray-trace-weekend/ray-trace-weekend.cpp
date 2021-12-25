// ray-trace-weekend.cpp : Defines the entry point for the application.
//

#include "ray-trace-weekend.h"
#include "vec3.h"
#include "color.h"

#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

using ColorC = Color<float>;
using Vec3C = Vec3<float>;

struct Box {
  size_t height;
  size_t width;
};

struct Loc {
  size_t row;
  size_t col;
};

constexpr size_t to_index(size_t row, size_t col, Box box) {
  return row * box.width + col;
}

constexpr Loc to_loc(size_t index, Box box) {
  return {index / box.width, index % box.height};
}

void write_ppm(const string& filename,
               const Box& box,
               vector<ColorC> pixels) {
  assert(pixels.size() >= box.width * box.height);
  ofstream file(filename);

  file << "P3\n" << box.width << " " << box.height << "\n255\n";
  for (size_t row = 0; row < box.height; ++row) {
    std::cerr << "\rScanlines remaining: " << row << ' ' << std::flush;
    for (size_t col = 0; col < box.width; ++col) {
      size_t index = to_index(row, col, box);
      const auto& p = pixels[index];
      p.write(file);
    }
  }
  file.close();
  std::cerr << "Donezo\n";
}

vector<ColorC> make_gradient(const Box& box) {
  vector<ColorC> pixels;
  pixels.reserve(box.width * box.height);

  for (size_t j = 0; j < box.height; ++j) {
    for (size_t i = 0; i < box.width; ++i) {
      auto r = float(i) / (box.width - 1);
      auto g = float(box.height - j - 1) / (box.height - 1);
      auto b = 0.25f;

      pixels.emplace_back(r, g, b);
    }
  }
  return pixels;
}

int main() {
  Vec3<float> v;
  Box b{256, 256};
  write_ppm("test.ppm", b, make_gradient(b));
  std::cerr << v << std::endl;
  return 0;
}
