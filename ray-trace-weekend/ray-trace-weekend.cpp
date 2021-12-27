// ray-trace-weekend.cpp : Defines the entry point for the application.
//

#include "ray-trace-weekend.h"
#include "camera.h"
#include "renderer.h"
#include "scene.h"
#include "vec3.h"
#include "material.h"

#include <memory>
#include <chrono>

using namespace std;

int main() {
  NumType aspect_ratio = 16.0 / 9.0;
  Vec3C camera_loc(0, 0, 0);
  NumType view_height = 2;
  NumType view_width = view_height * aspect_ratio;
  NumType focal_length = 1;
  auto camera = Camera(camera_loc, view_width, view_height, focal_length);
  auto scene = Scene();
  shared_ptr<Material> normal_material = std::make_shared<NormalMaterial>();
  shared_ptr<Material> gradient_material = std::make_shared<GradientMaterial>(ColorC(0.5, 0.7, 1), ColorC(1, 1, 1));
  shared_ptr<Material> diffuse_material =
      std::make_shared<DiffuseMaterial>(ColorC(0.7, 0.3, 0.3));
  shared_ptr<Material> gray_diffuse =
      std::make_shared<DiffuseMaterial>(ColorC(0.2, 0.2, 0.2));
  shared_ptr<Material> metal_material =
      std::make_shared<MetalMaterial>(ColorC(0.7, 0.7, 0.2));
  shared_ptr<Material> gray_metal_material =
      std::make_shared<MetalMaterial>(ColorC(0.3, 0.3, 0.3));
  scene.take_object(
      make_unique<BackgroundWall>(Vec3C(0, 0, -2), gradient_material));
  scene.take_object(
      make_unique<Sphere>(Vec3C(0, 0, -1), 0.5, diffuse_material));
  scene.take_object(
      make_unique<Sphere>(Vec3C(0.75, 0, -0.8), 0.25, metal_material));
  scene.take_object(
      make_unique<Sphere>(Vec3C(0, -20.5, -1), 20, gray_diffuse));
  scene.take_object(
      make_unique<Sphere>(Vec3C(1.7, -0.3, -1), 0.3, gray_diffuse));
  scene.take_object(
      make_unique<Sphere>(Vec3C(-0.8, -0.3, -1), 0.2, gray_metal_material));
  auto depth = 10;
  scene.set_max_depth(depth);
  std::cout << "Depth: " << depth << std::endl;


  size_t image_width = 400;
  size_t image_height = static_cast<size_t>(image_width / aspect_ratio);
  string filename = "test.ppm";
  auto r = Renderer({image_height, image_width}, filename, 30);

  r.render(scene, camera, true);
  const auto startTime = std::chrono::high_resolution_clock::now();
  r.render(scene, camera, false);
  const auto endTime = std::chrono::high_resolution_clock::now();
  std::cout << "Time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(endTime -
                                                                     startTime)
                   .count()
            << std::endl;

  return 0;
}
