#pragma once

#include <cstdint>

#include "Image.hpp"

namespace image_processing {

// Flips the image horizontally.
void flip_horizontal(Image& img);

// Flips the image vertically.
void flip_vertical(Image& img);

// Resizes the image to the specified width and height.
std::unique_ptr<Image> resize(const Image& img, int new_width, int new_height);

// Inverts the colors of the image.
void invert_colors(Image& img);

// Rotates the image 90 degrees clockwise.
std::unique_ptr<Image> rotate(const Image& img);

// Rotates the image by an arbitrary angle.
void rotate_image(Image& img, float angle);

// Adjusts the brightness of the image by a specified value (-255 to 255).
void adjust_brightness(Image& img, int adjustment);

// Adjusts the contrast of the image by a specified factor (0.0 to 10.0).
void adjust_contrast(Image& img, float factor);

// Converts an RGB image to grayscale.
void grayscale(const Image& img, Image& output);

// Sharpens the image using a kernel.
void sharpen(Image& img);

// Detects edges in the image using a Laplacian kernel.
void edge_detection(Image& img);

// Applies Gaussian blur to the image.
void gaussian_blur(Image& img);

}  // namespace image_processing
