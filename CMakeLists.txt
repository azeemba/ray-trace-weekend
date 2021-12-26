# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("ray-trace-weekend")
set(CMAKE_CXX_STANDARD 17)

enable_testing()

# Include sub-projects.
add_subdirectory ("ray-trace-weekend")
add_subdirectory ("tests")
