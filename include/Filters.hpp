#pragma once

#include "Image.hpp"

namespace image_processing {

// Applies a grayscale filter to the given image
void grayscale(Image& img);

// Flips the given image horizontally
void flip_horizontal(Image& img);

// Flips the given image vertically
void flip_vertical(Image& img);

// Resizes the given image to the specified width and height
Image resize(const Image& img, int new_width, int new_height);

// Rotates the given image 90 degrees counterclockwise
Image rotate(const Image& img);

// Applies an edge detection filter to the given image
void edge_detection(Image& img);

// Applies a Gaussian blur to the given image
void gaussian_blur(Image& img);

}  // namespace image_processing
