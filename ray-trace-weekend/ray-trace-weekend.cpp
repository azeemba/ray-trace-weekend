// ray-trace-weekend.cpp : Defines the entry point for the application.
//

#include "ray-trace-weekend.h"
#include "vec3.h"
#include "scene.h"
#include "camera.h"
#include "renderer.h"

using namespace std;

int main() {
  NumType aspect_ratio = 16.0 / 9.0;
  Vec3C camera_loc(0, 0, 0);
  NumType view_height = 2;
  NumType view_width = view_height * aspect_ratio;
  NumType focal_length = 1;
  auto camera = Camera(camera_loc, view_width, view_height, focal_length);
  auto scene = Scene();

  size_t image_width = 4000;
  size_t image_height = static_cast<size_t>(image_width / aspect_ratio);
  string filename = "test.ppm";
  auto r = Renderer({image_height, image_width}, filename);
  r.render(scene, camera);

  return 0;
}
