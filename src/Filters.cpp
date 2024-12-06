#include "Filters.hpp"

#include <execution>  // Parallel execution policies
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <vector>

#include "Image.hpp"

namespace image_processing {

void grayscale(Image& img) {
    if (img.getChannels() < 3) {
        throw std::runtime_error("Image must be RGB!");
    }

    auto rows = std::views::iota(0, img.getHeight());
    std::vector<int> row_indices(rows.begin(), rows.end());

    std::for_each(
        std::execution::par, row_indices.begin(), row_indices.end(),
        [&img](int i) {
            for (int j = 0; j < img.getWidth(); ++j) {
                int idx    = (i * img.getWidth() + j) * img.getChannels();
                auto& data = img.getData();
                uint8_t r  = data[idx];
                uint8_t g  = data[idx + 1];
                uint8_t b  = data[idx + 2];
                uint8_t gray =
                    static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
                data[idx]     = gray;
                data[idx + 1] = gray;
                data[idx + 2] = gray;
            }
        });
}

void flip_horizontal(Image& img) {
    auto rows = std::views::iota(0, img.getHeight());

    std::for_each(std::execution::par, rows.begin(), rows.end(), [&img](int i) {
        for (int j = 0; j < img.getWidth() / 2; ++j) {
            int left_idx  = (i * img.getWidth() + j) * img.getChannels();
            int right_idx = (i * img.getWidth() + (img.getWidth() - j - 1)) *
                            img.getChannels();

            for (int c = 0; c < img.getChannels(); ++c) {
                std::swap(img.getData()[left_idx + c],
                          img.getData()[right_idx + c]);
            }
        }
    });
}

void flip_vertical(Image& img) {
    auto cols = std::views::iota(0, img.getWidth());

    std::for_each(std::execution::par, cols.begin(), cols.end(), [&img](int j) {
        for (int i = 0; i < img.getHeight() / 2; ++i) {
            int top_idx    = (i * img.getWidth() + j) * img.getChannels();
            int bottom_idx = ((img.getHeight() - i - 1) * img.getWidth() + j) *
                             img.getChannels();

            for (int c = 0; c < img.getChannels(); ++c) {
                std::swap(img.getData()[top_idx + c],
                          img.getData()[bottom_idx + c]);
            }
        }
    });
}

Image resize(const Image& img, int new_width, int new_height) {
    Image resized(new_width, new_height, img.getChannels());

    auto rows     = std::views::iota(0, new_height);
    float x_ratio = static_cast<float>(img.getWidth()) / new_width;
    float y_ratio = static_cast<float>(img.getHeight()) / new_height;

    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j = 0; j < new_width; ++j) {
            int src_x   = static_cast<int>(j * x_ratio);
            int src_y   = static_cast<int>(i * y_ratio);
            int src_idx = (src_y * img.getWidth() + src_x) * img.getChannels();
            int dst_idx = (i * new_width + j) * img.getChannels();

            for (int c = 0; c < img.getChannels(); ++c) {
                resized.getData()[dst_idx + c] = img.getData()[src_idx + c];
            }
        }
    });

    return resized;
}

Image rotate(const Image& img) {
    Image rotated(img.getHeight(), img.getWidth(), img.getChannels());

    auto rows = std::views::iota(0, img.getHeight());

    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j = 0; j < img.getWidth(); ++j) {
            int src_idx = (i * img.getWidth() + j) * img.getChannels();
            int dst_idx = (j * img.getHeight() + (img.getHeight() - i - 1)) *
                          img.getChannels();

            for (int c = 0; c < img.getChannels(); ++c) {
                rotated.getData()[dst_idx + c] = img.getData()[src_idx + c];
            }
        }
    });

    return rotated;
}

void edge_detection(Image& img) {
    const int kernel[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};

    Image result(img.getWidth(), img.getHeight(), img.getChannels());

    auto rows = std::views::iota(1, img.getHeight() - 1);

    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j = 1; j < img.getWidth() - 1; ++j) {
            for (int c = 0; c < img.getChannels(); ++c) {
                int sum = 0;

                for (int ki = -1; ki <= 1; ++ki) {
                    for (int kj = -1; kj <= 1; ++kj) {
                        int src_idx = ((i + ki) * img.getWidth() + (j + kj)) *
                                          img.getChannels() +
                                      c;
                        sum += kernel[ki + 1][kj + 1] * img.getData()[src_idx];
                    }
                }

                int dst_idx = (i * img.getWidth() + j) * img.getChannels() + c;
                result.getData()[dst_idx] = std::clamp(sum, 0, 255);
            }
        }
    });

    img = result;
}

void gaussian_blur(Image& img) {
    const float kernel[3][3] = {{1 / 16.0f, 2 / 16.0f, 1 / 16.0f},
                                {2 / 16.0f, 4 / 16.0f, 2 / 16.0f},
                                {1 / 16.0f, 2 / 16.0f, 1 / 16.0f}};

    Image result(img.getWidth(), img.getHeight(), img.getChannels());

    auto rows = std::views::iota(1, img.getHeight() - 1);

    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j = 1; j < img.getWidth() - 1; ++j) {
            for (int c = 0; c < img.getChannels(); ++c) {
                float sum = 0;

                for (int ki = -1; ki <= 1; ++ki) {
                    for (int kj = -1; kj <= 1; ++kj) {
                        int src_idx = ((i + ki) * img.getWidth() + (j + kj)) *
                                          img.getChannels() +
                                      c;
                        sum += kernel[ki + 1][kj + 1] * img.getData()[src_idx];
                    }
                }

                int dst_idx = (i * img.getWidth() + j) * img.getChannels() + c;
                result.getData()[dst_idx] =
                    static_cast<uint8_t>(std::clamp(sum, 0.0f, 255.0f));
            }
        }
    });

    img = result;
}

}  // namespace image_processing
