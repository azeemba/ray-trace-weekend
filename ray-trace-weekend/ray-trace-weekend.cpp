// ray-trace-weekend.cpp : Defines the entry point for the application.
//

#include "ray-trace-weekend.h"
#include "camera.h"
#include "renderer.h"
#include "scene.h"
#include "vec3.h"

#include <memory>

using namespace std;

int main() {
  NumType aspect_ratio = 16.0 / 9.0;
  Vec3C camera_loc(0, 0, 0);
  NumType view_height = 2;
  NumType view_width = view_height * aspect_ratio;
  NumType focal_length = 1;
  auto camera = Camera(camera_loc, view_width, view_height, focal_length);
  auto scene = Scene();
  scene.take_object(
      make_unique<BackgroundWall>(Vec3C(0, 0, -2), ColorC(0.5, 0.7, 1)));
  scene.take_object(
      make_unique<Sphere>(Vec3C(0, 0, -1), 0.5, ColorC(1, 0, 0)));
  scene.take_object(
      make_unique<Sphere>(Vec3C(0, -21, -1.5), 20, ColorC(1, 1, 0)));
  scene.take_object(
      make_unique<Sphere>(Vec3C(1.7, -1, -1.5), 0.3, ColorC(0, 1, 0.8)));
  scene.take_object(
      make_unique<Sphere>(Vec3C(-1, -1, -1.8), 0.2, ColorC(0.3, 0.8, 0.8)));


  size_t image_width = 400;
  size_t image_height = static_cast<size_t>(image_width / aspect_ratio);
  string filename = "test.ppm";
  auto r = Renderer({image_height, image_width}, filename, 30);
  r.render(scene, camera);

  return 0;
}
