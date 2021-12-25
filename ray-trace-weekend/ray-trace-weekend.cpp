// ray-trace-weekend.cpp : Defines the entry point for the application.
//

#include "ray-trace-weekend.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <cassert>
#include <fstream>
#include <vector>

#include <algorithm>
#include <numeric>

using namespace std;

using NumType = float;
using ColorC = Color<NumType>;
using Vec3C = Vec3<NumType>;
using RayC = Ray<NumType>;

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

vector<ColorC> make_gradient(const Box& box) {
  vector<ColorC> pixels;
  pixels.reserve(box.width * box.height);

  for (size_t j = 0; j < box.height; ++j) {
    for (size_t i = 0; i < box.width; ++i) {
      auto r = NumType(i) / (box.width - 1);
      auto g = NumType(box.height - j - 1) / (box.height - 1);
      auto b = 0.25f;

      pixels.emplace_back(r, g, b);
    }
  }
  return pixels;
}

class Scene {
  // store representation somehow

  ColorC hit_background(const RayC& ray) const {
    ColorC gradient_start(1, 1, 1);
    ColorC gradient_end(0.5, 0.7, 1.0);
    NumType unit_y = ray.dir().unit().y();
    NumType t = 0.5*(unit_y + 1.0);
    return gradient_start * (1.0 - t) + gradient_end * t;
  }

 public:
  ColorC fire_ray(const RayC& ray) const {
    // check if incident on any objects.
    // if not, delegate to background
    return hit_background(ray);
  }
};

class Camera {
  Vec3C _position;
  Vec3C _right_dir;
  Vec3C _up_dir;
  Vec3C _lower_left_point;

 public:
  Camera(const Vec3C& position,
         NumType view_width,
         NumType view_height,
         NumType focal_length)
      : _position(position) {
    _right_dir = Vec3C(view_width, 0, 0);
    _up_dir = Vec3C(0, view_height, 0);
    _lower_left_point = _position + Vec3C(0, 0, -focal_length) -
                        _right_dir * 0.5 - _up_dir * 0.5;
  }

  int scan_scene(const Scene& s, Box size, vector<ColorC>& frame) const {
    vector<size_t> indices(size.height * size.width);
    iota(indices.begin(), indices.end(), 0);

    transform(indices.begin(), indices.end(), frame.begin(),
              [&size, this, &s](size_t index) {
                Loc l = to_loc(index, size);
                NumType x_factor = NumType(l.col) / size.width;
                NumType y_factor = NumType(l.row) / size.height;
                RayC r(_position, _lower_left_point + _up_dir * y_factor +
                                      _right_dir * x_factor);
                return s.fire_ray(r);
              });
    return 0;
  }
};

class Renderer {
  Box _box;
  string _filename;

 public:
  Renderer(Box size, string filename) : _box(size), _filename(filename) {}
  void render(const Scene& s, const Camera& c) {
    vector<ColorC> frame(_box.width * _box.height);
    c.scan_scene(s, _box, frame);
    write_ppm(frame);
  }

 private:
  void write_ppm(vector<ColorC> pixels) {
    assert(pixels.size() >= _box.width * _box.height);
    ofstream file(_filename);

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
};

int main() {
  NumType aspect_ratio = 16.0 / 9.0;
  Vec3C camera_loc(0, 0, 0);
  NumType view_height = 2;
  NumType view_width = view_height * aspect_ratio;
  NumType focal_length = 1;
  auto camera = Camera(camera_loc, view_width, view_height, focal_length);
  auto scene = Scene();

  size_t image_width = 400;
  size_t image_height = static_cast<size_t>(image_width / aspect_ratio);
  string filename = "test.ppm";
  auto r = Renderer({image_height, image_width}, filename);
  r.render(scene, camera);

  return 0;
}
