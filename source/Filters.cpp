#include "Filters.hpp"

#include <execution>  // 包含并行执行策略
#include <execution>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <vector>

#include "Image.hpp"

void grayscale(Image& img) {
  if (img.channels < 3) {
    throw std::runtime_error("Image must be RGB!");
  }

  // 使用 Ranges 构造行索引
  auto rows = std::views::iota(0, img.height);

  // 转换为 vector，以便与 std::execution::par 配合使用
  std::vector<int> row_indices(rows.begin(), rows.end());

  // 并行处理每一行
  std::for_each(std::execution::par, row_indices.begin(), row_indices.end(),
                [&img](int i) {
                  for (int j = 0; j < img.width; ++j) {
                    int idx   = (i * img.width + j) * img.channels;
                    uint8_t r = img.data[idx];
                    uint8_t g = img.data[idx + 1];
                    uint8_t b = img.data[idx + 2];
                    uint8_t gray =
                        static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
                    img.data[idx]     = gray;
                    img.data[idx + 1] = gray;
                    img.data[idx + 2] = gray;
                  }
                });

  img.channels = 3;  // 更新通道数
}

void flip_horizontal(Image& img) {
  auto rows = std::views::iota(0, img.height);

  std::for_each(std::execution::par, rows.begin(), rows.end(), [&img](int i) {
    for (int j = 0; j < img.width / 2; ++j) {
      int left_idx  = (i * img.width + j) * img.channels;
      int right_idx = (i * img.width + (img.width - j - 1)) * img.channels;

      for (int c = 0; c < img.channels; ++c) {
        std::swap(img.data[left_idx + c], img.data[right_idx + c]);
      }
    }
  });
}

void flip_vertical(Image& img) {
  auto cols = std::views::iota(0, img.width);

  std::for_each(std::execution::par, cols.begin(), cols.end(), [&img](int j) {
    for (int i = 0; i < img.height / 2; ++i) {
      int top_idx    = (i * img.width + j) * img.channels;
      int bottom_idx = ((img.height - i - 1) * img.width + j) * img.channels;

      for (int c = 0; c < img.channels; ++c) {
        std::swap(img.data[top_idx + c], img.data[bottom_idx + c]);
      }
    }
  });
}

Image resize(const Image& img, int new_width, int new_height) {
  Image resized(new_width, new_height, img.channels);

  auto rows     = std::views::iota(0, new_height);
  float x_ratio = static_cast<float>(img.width) / new_width;
  float y_ratio = static_cast<float>(img.height) / new_height;

  std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
    for (int j = 0; j < new_width; ++j) {
      int src_x   = static_cast<int>(j * x_ratio);
      int src_y   = static_cast<int>(i * y_ratio);
      int src_idx = (src_y * img.width + src_x) * img.channels;
      int dst_idx = (i * new_width + j) * img.channels;

      for (int c = 0; c < img.channels; ++c) {
        resized.data[dst_idx + c] = img.data[src_idx + c];
      }
    }
  });

  return resized;
}

Image rotate(const Image& img) {
  Image rotated(img.height, img.width, img.channels);

  auto rows = std::views::iota(0, img.height);

  std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
    for (int j = 0; j < img.width; ++j) {
      int src_idx = (i * img.width + j) * img.channels;
      int dst_idx = (j * img.height + (img.height - i - 1)) * img.channels;

      for (int c = 0; c < img.channels; ++c) {
        rotated.data[dst_idx + c] = img.data[src_idx + c];
      }
    }
  });

  return rotated;
}

void edge_detection(Image& img) {
  const int kernel[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};

  Image result(img.width, img.height, img.channels);

  auto rows = std::views::iota(1, img.height - 1);

  std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
    for (int j = 1; j < img.width - 1; ++j) {
      for (int c = 0; c < img.channels; ++c) {
        int sum = 0;

        for (int ki = -1; ki <= 1; ++ki) {
          for (int kj = -1; kj <= 1; ++kj) {
            int src_idx = ((i + ki) * img.width + (j + kj)) * img.channels + c;
            sum += kernel[ki + 1][kj + 1] * img.data[src_idx];
          }
        }

        int dst_idx          = (i * img.width + j) * img.channels + c;
        result.data[dst_idx] = std::clamp(sum, 0, 255);
      }
    }
  });

  img = result;
}

void gaussian_blur(Image& img) {
  const float kernel[3][3] = {{1 / 16.0f, 2 / 16.0f, 1 / 16.0f},
                              {2 / 16.0f, 4 / 16.0f, 2 / 16.0f},
                              {1 / 16.0f, 2 / 16.0f, 1 / 16.0f}};

  Image result(img.width, img.height, img.channels);

  auto rows = std::views::iota(1, img.height - 1);

  std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
    for (int j = 1; j < img.width - 1; ++j) {
      for (int c = 0; c < img.channels; ++c) {
        float sum = 0;

        for (int ki = -1; ki <= 1; ++ki) {
          for (int kj = -1; kj <= 1; ++kj) {
            int src_idx = ((i + ki) * img.width + (j + kj)) * img.channels + c;
            sum += kernel[ki + 1][kj + 1] * img.data[src_idx];
          }
        }

        int dst_idx = (i * img.width + j) * img.channels + c;
        result.data[dst_idx] =
            static_cast<uint8_t>(std::clamp(sum, 0.0f, 255.0f));
      }
    }
  });

  img = result;
}
