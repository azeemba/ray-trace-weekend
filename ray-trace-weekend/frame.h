#pragma once

#include "color.h"
#include <vector>

struct Box {
  size_t height;
  size_t width;
};

struct Loc {
  size_t row;
  size_t col;
};

inline constexpr size_t to_index(size_t row, size_t col, Box box) {
  return row * box.width + col;
}

inline constexpr Loc to_loc(size_t index, Box box) {
  return {index / box.width, index % box.height};
}

inline std::vector<ColorC> initialize_frame(Box box) {
  return std::vector<ColorC>(box.width * box.height);
}
