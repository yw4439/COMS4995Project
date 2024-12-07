#include <iostream>
#include <stdexcept>

#include "Filters.hpp"
#include "Image.hpp"

using namespace image_processing;

int main() {
    try {
        Image input("input.png");
        std::cout << "Loaded image successfully: " << input.getWidth() << "x"
                  << input.getHeight() << " with " << input.getChannels()
                  << " channels." << std::endl;

        // Flip Horizontal Test
        Image flipped_horizontal = input;
        flip_horizontal(flipped_horizontal);
        flipped_horizontal.save("output_flip_horizontal.png");

        // Flip Vertical Test
        Image flipped_vertical = input;
        flip_vertical(flipped_vertical);
        flipped_vertical.save("output_flip_vertical.png");

        // Resize Test
        auto resized =
            resize(input, 200, 200);  // Use auto to handle unique_ptr
        resized->save("output_resized.png");

        // Invert Colors Test
        Image inverted = input;
        invert_colors(inverted);
        inverted.save("output_invert_colors.png");

        // Rotate Test
        auto rotated = rotate(input);
        rotated->save("output_rotate.png");

        // Rotate Arbitrary Test
        Image rotated_45 = input;
        rotate_image(rotated_45, 45.0f);
        rotated_45.save("output_rotate_45.png");

        // Adjust Brightness Test
        Image brightened = input;
        adjust_brightness(brightened, 50);
        brightened.save("output_brightness_adjusted.png");

        // Adjust Contrast Test
        Image contrast = input;
        adjust_contrast(contrast, 1.5f);
        contrast.save("output_contrast_adjusted.png");

        // Grayscale Test
        Image grayscale_img = input;
        grayscale(input, grayscale_img);
        grayscale_img.save("output_grayscale.png");

        // Sharpen Test
        Image sharpened = input;
        sharpen(sharpened);
        sharpened.save("output_sharpened.png");

        // Edge Detection Test
        Image edges = input;
        edge_detection(edges);
        edges.save("output_edge_detection.png");

        // Gaussian Blur Test
        Image blurred = input;
        gaussian_blur(blurred);
        blurred.save("output_blurred.png");

        std::cout << "All tests executed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
