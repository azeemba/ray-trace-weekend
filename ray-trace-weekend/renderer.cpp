
#include "renderer.h"
#include "camera.h"
#include "frame.h"
#include "random_helper.h"
#include "scene.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <execution>
#include <fstream>
#include <iostream>
#include <numeric>

#ifdef OPENCV_LOADED
#include <opencv2/opencv.hpp>
#endif

// Anon namespace

namespace {
#ifdef OPENCV_LOADED
cv::Mat vec_to_mat(std::vector<ColorC> pixels, const Box& box) {
  cv::Mat image = cv::Mat::zeros(box.height, box.width, CV_8UC3);
  for (size_t i = 0; i < box.height; ++i) {
    for (size_t j = 0; j < box.width; ++j) {
      auto& pixel = pixels[to_index(i, j, box)];
      auto& x = image.at<cv::Vec3b>(i, j);
      x[0] = pixel.ib();
      x[1] = pixel.ig();
      x[2] = pixel.ir();
    }
  }
  return image;
}
#endif
};  // namespace

Renderer::Renderer(Box size, std::string filename)
    : _box(size), _filename(filename) {}

ColorC Renderer::average_pixel(const Scene& s, const Camera& c, Loc pixel, size_t samples) {
  ColorC total_color;
  for (size_t i = 0; i < samples; ++i) {
    NumType x_factor =
        (NumType(pixel.col) + get_uniform_random(-0.5, 0.5)) / _box.width;
    NumType y_factor =
        (NumType(pixel.row) + get_uniform_random(-0.5, 0.5)) / _box.height;
    auto r = c.get_pixel_ray(x_factor, y_factor);
    total_color = total_color + s.fire_ray(r);
  }
  total_color = total_color / samples;
  total_color.gamma_correct(2);
  return total_color;
}

std::vector<ColorC> Renderer::render_frame(const Scene& s, const Camera& c, size_t samples) {
  auto frame = initialize_frame(_box);

  std::vector<size_t> indices(_box.height * _box.width);
  // could use iota views which saves the allocation but C++20, do we want it?
  iota(indices.begin(), indices.end(), 0);

  transform(std::execution::par_unseq, indices.begin(), indices.end(),
            frame.begin(), [this, &s, &c, samples](size_t index) {
              Loc l = to_loc(index, _box);
              return average_pixel(s, c, l, samples);
            });

  return frame;
}

void Renderer::render(const Scene& s, const Camera& c, bool save, size_t samples) {
  auto frame = render_frame(s, c, samples);
  if (save) {
    write_ppm(frame);
  } else {
    display_frame(frame);
  }
}

void Renderer::play_animation(Scene& s, Camera& c) {
#ifdef OPENCV_LOADED
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;

  s.set_max_depth(3);

  Vec3C camera_position(0, 0, 0);
  Vec3C camera_lookat(0, 0, -1);
  NumType focal = 1;

  NumType frames_per_rotation = 360;
  NumType per_frame_radians = (360.0 / frames_per_rotation) * PI / 180.0;

  NumType theta = 0;
  NumType direction = -1;
  int key = -1;
  while (key == -1) {
    const auto startTime = std::chrono::high_resolution_clock::now();

    // move camera in a circle
    Vec3C camera_position(std::sin(theta), 0, std::cos(theta) - 1);
    c.recompute_orientation(camera_position, camera_lookat, focal);
    theta += direction*per_frame_radians;

    if (theta < -PI / 2) {
      direction = 1;
    } else if (theta > PI / 2) {
      direction = -1;
    }

    auto pixels = render_frame(s, c, 10);
    auto image = vec_to_mat(pixels, _box);

    const auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << "Time: "
              << duration_cast<milliseconds>(endTime - startTime).count()
              << std::endl;

    cv::imshow("RayTracerWeekend", image);
    key = cv::pollKey();
  }
#endif
}

void Renderer::display_frame(const std::vector<ColorC>& pixels) {
#ifdef OPENCV_LOADED
  auto image = vec_to_mat(pixels, _box);
  cv::imshow("RayTracerWeekend", image);
  cv::waitKey(0);
#endif
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
