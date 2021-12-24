// ray-trace-weekend.cpp : Defines the entry point for the application.
//

#include "ray-trace-weekend.h"

#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

struct ColorFloats {
  float r;
  float g;
  float b;
};

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
               vector<ColorFloats> pixels) {
  assert(pixels.size() >= box.width * box.height);
  ofstream file(filename);

  file << "P3\n" << box.width << " " << box.height << "\n255\n";
  for (size_t row = 0; row < box.height; ++row) {
    for (size_t col = 0; col < box.width; ++col) {
      size_t index = to_index(row, col, box);
      const ColorFloats p = pixels[index];

      int ir = static_cast<int>(255.999 * p.r);
      int ig = static_cast<int>(255.999 * p.g);
      int ib = static_cast<int>(255.999 * p.b);

      file << ir << " " << ig << " " << ib << "\n";
    }
  }
  file.close();
}

vector<ColorFloats> make_gradient(const Box& box) {
  vector<ColorFloats> pixels;
  pixels.reserve(box.width * box.height);

  for (size_t j = 0; j < box.height; ++j) {
    for (size_t i = 0; i < box.width; ++i) {
      auto r = float(i) / (box.width - 1);
      auto g = float(box.height - j) / (box.height - 1);
      auto b = 0.25f;

      pixels.push_back(ColorFloats{r, g, b});
    }
  }
  return pixels;
}

int main() {
  Box b{256, 256};
  write_ppm("test.ppm", b, make_gradient(b));
  return 0;
}
