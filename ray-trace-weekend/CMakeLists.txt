# CMakeList.txt : CMake project for ray-trace-weekend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# Add source to this project's executable.
add_executable (ray-trace-weekend "ray-trace-weekend.cpp" "ray-trace-weekend.h" "ray.h" "scene.h" "scene.cpp" "base_numeric.h" "camera.h" "camera.cpp" "renderer.h" "renderer.cpp" "frame.h" "primitives.h" "primitives.cpp" "material.h" "material.cpp" "random_helper.h" "random_helper.cpp")

# SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/PROFILE")
# TODO: Add tests and install targets if needed.
add_library(lib-ray-trace-weekend "base_numeric.h" "camera.h" "camera.cpp" "color.h" "frame.h" "primitives.cpp" "primitives.h" "ray.h" "renderer.cpp" "renderer.h" "scene.cpp" "scene.h" "vec3.h" "material.h" "material.cpp" "random_helper.h" "random_helper.cpp")

find_package(OpenCV)
message(WARNING, ${OpenCV_VERSION})
if (DEFINED OpenCV_VERSION) 
  message(WARNING, ${OpenCV_VERSION})
  add_definitions(-DOPENCV_LOADED)
  include_directories(${OpenCV_INCLUDE_DIRS})
  target_link_libraries(ray-trace-weekend ${OpenCV_LIBS})
endif()
