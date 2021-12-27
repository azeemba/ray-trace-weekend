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

