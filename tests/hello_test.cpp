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

TEST(Camera, Recompute) {
  Vec3C origin;
  NumType view_width = 2;
  NumType view_height = 1;
  Camera c(origin,view_width, view_height, 1);

  RayC orig_ray = c.get_pixel_ray(1, 1);

  c.recompute_orientation(origin, Vec3C(0, 0, -1), 1);
  RayC comp_ray = c.get_pixel_ray(1, 1);

  for (int i = 0; i < 3; ++i) {
    std::cout << "i: " << i << std::endl;
    EXPECT_NEAR(orig_ray.origin()[i], comp_ray.origin()[i], 0.001);
    EXPECT_NEAR(orig_ray.dir()[i], comp_ray.dir()[i], 0.001);
  }
}
