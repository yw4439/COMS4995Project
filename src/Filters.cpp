#include <algorithm>
#include <cmath>
#include <execution>  // Parallel execution policies
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <vector>

#include "Filters.hpp"
#include "Image.hpp"

namespace image_processing {

void flip_horizontal(Image& img) {
    auto rows = std::views::iota(0, img.getHeight());

    std::for_each(std::execution::par, rows.begin(), rows.end(), [&img](int i) {
        for (int j : std::views::iota(0, img.getWidth() / 2)) {
            int left_idx  = (i * img.getWidth() + j) * img.getChannels();
            int right_idx = (i * img.getWidth() + (img.getWidth() - j - 1)) *
                            img.getChannels();

            for (int c : std::views::iota(0, img.getChannels())) {
                std::swap(img.getData()[left_idx + c],
                          img.getData()[right_idx + c]);
            }
        }
    });
}

void flip_vertical(Image& img) {
    auto cols = std::views::iota(0, img.getWidth());

    std::for_each(std::execution::par, cols.begin(), cols.end(), [&img](int j) {
        for (int i : std::views::iota(0, img.getHeight() / 2)) {
            int top_idx    = (i * img.getWidth() + j) * img.getChannels();
            int bottom_idx = ((img.getHeight() - i - 1) * img.getWidth() + j) *
                             img.getChannels();

            for (int c : std::views::iota(0, img.getChannels())) {
                std::swap(img.getData()[top_idx + c],
                          img.getData()[bottom_idx + c]);
            }
        }
    });
}

std::unique_ptr<Image> resize(const Image& img, int new_width, int new_height) {
    auto resized =
        std::make_unique<Image>(new_width, new_height, img.getChannels());

    auto rows     = std::views::iota(0, new_height);
    float x_ratio = static_cast<float>(img.getWidth()) / new_width;
    float y_ratio = static_cast<float>(img.getHeight()) / new_height;

    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j : std::views::iota(0, new_width)) {
            int src_x   = static_cast<int>(j * x_ratio);
            int src_y   = static_cast<int>(i * y_ratio);
            int src_idx = (src_y * img.getWidth() + src_x) * img.getChannels();
            int dst_idx = (i * new_width + j) * img.getChannels();

            for (int c : std::views::iota(0, img.getChannels())) {
                resized->getData()[dst_idx + c] = img.getData()[src_idx + c];
            }
        }
    });

    return resized;
}

void invert_colors(Image& img) {
    // Create a range of rows
    auto rows = std::views::iota(0, img.getHeight());

    // Apply color inversion in parallel
    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j : std::views::iota(0, img.getWidth())) {
            for (int c : std::views::iota(0, img.getChannels())) {
                int idx = (i * img.getWidth() + j) * img.getChannels() + c;
                img.getData()[idx] =
                    255 - img.getData()[idx];  // Invert the color value
            }
        }
    });
}

std::unique_ptr<Image> rotate(const Image& img) {
    auto rotated = std::make_unique<Image>(img.getHeight(), img.getWidth(),
                                           img.getChannels());

    auto rows = std::views::iota(0, img.getHeight());

    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j : std::views::iota(0, img.getWidth())) {
            int src_idx = (i * img.getWidth() + j) * img.getChannels();
            int dst_idx = (j * img.getHeight() + (img.getHeight() - i - 1)) *
                          img.getChannels();

            for (int c : std::views::iota(0, img.getChannels())) {
                rotated->getData()[dst_idx + c] = img.getData()[src_idx + c];
            }
        }
    });

    return rotated;
}

void rotate_image(Image& img, float angle) {
    // Convert angle from degrees to radians
    float radians = angle * M_PI / 180.0f;

    // Calculate sine and cosine of the angle
    float cos_theta = std::cos(radians);
    float sin_theta = std::sin(radians);

    // Calculate the original image's corners after rotation
    int width  = img.getWidth();
    int height = img.getHeight();

    int new_width  = static_cast<int>(std::abs(width * cos_theta) +
                                      std::abs(height * sin_theta));
    int new_height = static_cast<int>(std::abs(width * sin_theta) +
                                      std::abs(height * cos_theta));

    // Calculate the new center point of the resulting image
    int new_centerX = new_width / 2;
    int new_centerY = new_height / 2;

    // Calculate the original image's center point
    int old_centerX = width / 2;
    int old_centerY = height / 2;

    // Create a new image to store the rotated result
    Image result(new_width, new_height, img.getChannels());

    auto rows = std::views::iota(0, new_height);

    // Rotate each pixel in parallel
    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j : std::views::iota(0, new_width)) {
            // Translate (j, i) to center of new image
            int x = j - new_centerX;
            int y = i - new_centerY;

            // Apply reverse rotation to find corresponding coordinates in
            // original image
            int orig_x =
                static_cast<int>(x * cos_theta + y * sin_theta) + old_centerX;
            int orig_y =
                static_cast<int>(-x * sin_theta + y * cos_theta) + old_centerY;

            // Check if original coordinates are within bounds
            if (orig_x >= 0 && orig_x < width && orig_y >= 0 &&
                orig_y < height) {
                for (int c : std::views::iota(0, img.getChannels())) {
                    int src_idx =
                        (orig_y * width + orig_x) * img.getChannels() + c;
                    int dst_idx = (i * new_width + j) * img.getChannels() + c;
                    result.getData()[dst_idx] = img.getData()[src_idx];
                }
            }
        }
    });

    // Update the image with the newly rotated result
    img = result;
}

void adjust_brightness(Image& img, int adjustment) {
    // Ensure adjustment value is within valid range (-255 to 255)
    if (adjustment < -255 || adjustment > 255) {
        throw std::invalid_argument(
            "Adjustment value must be between -255 and 255.");
    }

    auto rows = std::views::iota(0, img.getHeight());

    // Adjust brightness in parallel
    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j : std::views::iota(0, img.getWidth())) {
            for (int c : std::views::iota(0, img.getChannels())) {
                int idx = (i * img.getWidth() + j) * img.getChannels() + c;
                img.getData()[idx] =
                    std::clamp(img.getData()[idx] + adjustment, 0, 255);
            }
        }
    });
}

void adjust_contrast(Image& img, float factor) {
    // Ensure factor value is within valid range (e.g., 0.0 to 10.0 for
    // reasonable contrast adjustments)
    if (factor < 0.0f || factor > 10.0f) {
        throw std::invalid_argument(
            "Contrast factor must be between 0.0 and 10.0.");
    }

    auto rows = std::views::iota(0, img.getHeight());

    // Calculate midpoint for contrast adjustment
    const float midpoint = 128.0f;

    // Adjust contrast in parallel
    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j : std::views::iota(0, img.getWidth())) {
            for (int c : std::views::iota(0, img.getChannels())) {
                int idx = (i * img.getWidth() + j) * img.getChannels() + c;

                // Apply contrast formula: new_value = midpoint + factor *
                // (old_value - midpoint)
                int new_value = static_cast<int>(
                    midpoint + factor * (img.getData()[idx] - midpoint));

                // Clamp the result to ensure valid pixel range
                img.getData()[idx] = std::clamp(new_value, 0, 255);
            }
        }
    });
}

void grayscale(const Image& img, Image& output) {
    if (img.getChannels() < 3) {
        throw std::runtime_error("Image must be RGB!");
    }

    auto& input_data  = img.getData();
    auto& output_data = output.getData();

    auto rows = std::views::iota(0, img.getHeight());
    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j : std::views::iota(0, img.getWidth())) {
            int idx   = (i * img.getWidth() + j) * img.getChannels();
            uint8_t r = input_data[idx];
            uint8_t g = input_data[idx + 1];
            uint8_t b = input_data[idx + 2];
            uint8_t gray =
                static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
            output_data[idx]     = gray;
            output_data[idx + 1] = gray;
            output_data[idx + 2] = gray;
        }
    });
}

void sharpen(Image& img) {
    const int kernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

    Image result(img.getWidth(), img.getHeight(), img.getChannels());

    auto rows = std::views::iota(1, img.getHeight() - 1);

    // Apply sharpening in parallel
    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j : std::views::iota(1, img.getWidth() - 1)) {
            for (int c : std::views::iota(0, img.getChannels())) {
                int sum = 0;

                for (int ki : std::views::iota(-1, 2)) {
                    for (int kj : std::views::iota(-1, 2)) {
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

void edge_detection(Image& img) {
    const int kernel[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};

    Image result(img.getWidth(), img.getHeight(), img.getChannels());

    auto rows = std::views::iota(1, img.getHeight() - 1);

    std::for_each(std::execution::par, rows.begin(), rows.end(), [&](int i) {
        for (int j : std::views::iota(1, img.getWidth() - 1)) {
            for (int c : std::views::iota(0, img.getChannels())) {
                int sum = 0;

                for (int ki : std::views::iota(-1, 2)) {
                    for (int kj : std::views::iota(-1, 2)) {
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
        for (int j : std::views::iota(1, img.getWidth() - 1)) {
            for (int c : std::views::iota(0, img.getChannels())) {
                float sum = 0;

                for (int ki : std::views::iota(-1, 2)) {
                    for (int kj : std::views::iota(-1, 2)) {
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
