#pragma once

#include "Image.hpp"

namespace image_processing {

// Applies a grayscale filter to the image.
void grayscale(Image& img);

// Flips the image horizontally.
void flip_horizontal(Image& img);

// Flips the image vertically.
void flip_vertical(Image& img);

// Resizes the image to the specified width and height.
Image resize(const Image& img, int new_width, int new_height);

// Rotates the image 90 degrees clockwise.
Image rotate(const Image& img);

// Rotates the image by an arbitrary angle.
void rotate_image(Image& img, float angle);

// Adjusts the brightness of the image by the specified adjustment value (-255
// to 255).
void adjust_brightness(Image& img, int adjustment);

// Adjusts the contrast of the image by the specified factor (0.0 to 10.0).
void adjust_contrast(Image& img, float factor);

// Applies a sharpening filter to the image.
void sharpen(Image& img);

// Applies edge detection to the image.
void edge_detection(Image& img);

// Applies a Gaussian blur to the image.
void gaussian_blur(Image& img);

}  // namespace image_processing
