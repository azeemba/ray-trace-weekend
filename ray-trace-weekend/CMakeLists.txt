# CMakeList.txt : CMake project for ray-trace-weekend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (ray-trace-weekend "ray-trace-weekend.cpp" "ray-trace-weekend.h" "ray.h" "scene.h" "scene.cpp" "base_numeric.h" "camera.h" "camera.cpp" "renderer.h" "renderer.cpp" "frame.h" "primitives.h" "primitives.cpp" "material.h" "material.cpp" "random_helper.h" "random_helper.cpp")

# TODO: Add tests and install targets if needed.
add_library(lib-ray-trace-weekend "base_numeric.h" "camera.h" "camera.cpp" "color.h" "frame.h" "primitives.cpp" "primitives.h" "ray.h" "renderer.cpp" "renderer.h" "scene.cpp" "scene.h" "vec3.h" "material.h" "material.cpp" "random_helper.h" "random_helper.cpp")
