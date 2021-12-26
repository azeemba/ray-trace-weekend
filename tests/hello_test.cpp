#include <gtest/gtest.h>

#include <memory>

#include <ray-trace-weekend/camera.h>
#include <ray-trace-weekend/color.h>
#include <ray-trace-weekend/primitives.h>
#include <ray-trace-weekend/ray.h>
#include <ray-trace-weekend/scene.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(Sphere, Color) {
  auto c = ColorC(0.1, 0.2, 0.3);
  auto s = Sphere(Vec3C(), 1, c);

  auto ret = s.get_color(Vec3C());
  EXPECT_EQ(ret.r(), c.r());
  EXPECT_EQ(ret.g(), c.g());
  EXPECT_EQ(ret.b(), c.b());
}

TEST(Sphere, Ray) {
  // For rays coming from far,
  // the sillhouete of the sphere is
  // all the matters
  auto center = Vec3C(0, 0, 10);
  NumType radius = 0.5;
  auto s = Sphere(center, radius);
  auto origin = Vec3C();
  NumType z = 1;

  auto ray_dir = Vec3C(0, 0.013, 1);
  RayC ray(origin, ray_dir);
  while (ray_dir[1] * 10 < radius) {
    std::cout << ray_dir << std::endl;
    auto t = s.collide_ray(ray);
    EXPECT_NE(t, -1);
    EXPECT_LT(t, 10.01);
    std::cout << ray.at(t) << std::endl;
    ray_dir[1] += 0.003;
    ray = RayC(origin, ray_dir);
  }
  EXPECT_EQ(s.collide_ray(ray), -1);
}

TEST(Sphere, CloseUpValidateT) {
  Vec3C center(0, 0, -1);
  NumType radius = 0.5;
  Sphere sphere(center, radius);

  Vec3C origin(0, 0, 0);
  Vec3C dir(0, 0.11, -1);
  RayC ray(origin, dir);
  while (ray.dir()[1] < radius) {
    std::cout << ray.dir() << std::endl;
    auto t = sphere.collide_ray(ray);
    EXPECT_NE(t, -1);

    auto intersection = ray.at(t);
    auto dist = (intersection - center).length();
    EXPECT_NEAR(dist, radius, 0.0001);

    dir[1] += 0.003;
    ray = RayC(origin, dir);
  }
}

TEST(Scene, Ray) {
  auto scene = Scene();
  auto bgColor = ColorC(1, 1, 1);
  BackgroundWall wall(Vec3C(0, 0, 11), bgColor);
  auto sphereColor = ColorC(0, 0.7, 1);
  NumType radius = 0.5;
  Sphere sphere(Vec3C(0, 0, 10), radius, sphereColor);

  scene.take_object(std::make_unique<BackgroundWall>(wall));
  scene.take_object(std::make_unique<Sphere>(sphere));

  auto origin = Vec3C();
  NumType z = 1;
  auto ray_dir = Vec3C(0, 0.013, 1);
  RayC ray(origin, ray_dir);

  while (ray_dir[1] * 10 < radius) {
    std::cout << ray_dir << std::endl;
    auto c = scene.fire_ray(ray);
    EXPECT_EQ(c.r(), sphereColor.r());
    EXPECT_EQ(c.g(), sphereColor.g());
    EXPECT_EQ(c.b(), sphereColor.b());
    ray_dir[1] += 0.003;
    ray = RayC(origin, ray_dir);
  }
  auto c = scene.fire_ray(ray);
  EXPECT_EQ(c.r(), bgColor.r());
  EXPECT_EQ(c.g(), bgColor.g());
  EXPECT_EQ(c.b(), bgColor.b());
}

TEST(Scene, CloseUp) {
  auto scene = Scene();
  auto bgColor = ColorC(1, 1, 1);
  BackgroundWall wall(Vec3C(0, 0, 2), bgColor);
  auto sphereColor = ColorC(0, 0.7, 1);
  NumType radius = 0.5;
  Sphere sphere(Vec3C(0, 0, -1), radius, sphereColor);

  scene.take_object(std::make_unique<BackgroundWall>(wall));
  scene.take_object(std::make_unique<Sphere>(sphere));

  Vec3C origin(0, 0, 0);
  Vec3C dir(0, 0.11, -1);
  RayC ray(origin, dir);

  while (ray.dir()[1] < radius) {
    std::cout << ray.dir() << std::endl;
    auto c = scene.fire_ray(ray);
    EXPECT_EQ(c.r(), sphereColor.r());
    EXPECT_EQ(c.g(), sphereColor.g());
    EXPECT_EQ(c.b(), sphereColor.b());
    dir[1] += 0.003;
    ray = RayC(origin, dir);
  }
}

TEST(Camera, CloseUp) {
  auto scene = Scene();
  auto bgColor = ColorC(1, 1, 1);
  BackgroundWall wall(Vec3C(0, 0, 2), bgColor);
  auto sphereColor = ColorC(0, 0.7, 1);
  NumType radius = 0.5;
  Sphere sphere(Vec3C(0, 0, -1), radius, sphereColor);

  scene.take_object(std::make_unique<BackgroundWall>(wall));
  scene.take_object(std::make_unique<Sphere>(sphere));

  Vec3C origin(0, 0, 0);
  Camera cam(origin, 2, 1, 1);
  Box box{100, 200};
  std::vector<ColorC> frame(box.height * box.width);
  ASSERT_EQ(frame.size(), box.height * box.width);

  cam.scan_scene(scene, box, frame);

  NumType x_per_pixel = 2.0 / box.width;
  NumType y_per_pixel = 1.0 / box.height;

  size_t x_center_index = box.width / 2;
  size_t y_center_index = box.height / 2;

  for (size_t i = 0; i < frame.size(); ++i) {
    size_t row = i / box.width;
    size_t col = i % box.width;
    NumType y_dist = (row - y_center_index) * y_per_pixel;
    NumType x_dist = (col - x_center_index) * x_per_pixel;
    if (y_dist * y_dist + x_dist * x_dist < radius * radius) {
      auto& c = frame[i];
      EXPECT_EQ(c.r(), sphereColor.r());
      EXPECT_EQ(c.g(), sphereColor.g());
      EXPECT_EQ(c.b(), sphereColor.b());
    }
  }
}
