#include <iostream>
#include <stdexcept>
#include <string>

#include "Image.hpp"

using namespace image_processing;

void test_load_image() {
    try {
        Image img("input.png");
        std::cout << "Loaded image successfully: " << img.getWidth() << "x"
                  << img.getHeight() << " with " << img.getChannels()
                  << " channels." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "test_load_image failed: " << e.what() << std::endl;
    }
}

void test_save_image() {
    try {
        Image img("input.png");
        img.save("output_test.png");
        std::cout << "Saved image successfully to output_test.png."
                  << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "test_save_image failed: " << e.what() << std::endl;
    }
}

void test_flip_horizontal() {
    try {
        Image img("input.png");
        flip_horizontal(img);
        img.save("output_flip_horizontal.png");
        std::cout << "Flip horizontal succeeded and saved to "
                     "output_flip_horizontal.png."
                  << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "test_flip_horizontal failed: " << e.what() << std::endl;
    }
}

void test_flip_vertical() {
    try {
        Image img("input.png");
        flip_vertical(img);
        img.save("output_flip_vertical.png");
        std::cout
            << "Flip vertical succeeded and saved to output_flip_vertical.png."
            << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "test_flip_vertical failed: " << e.what() << std::endl;
    }
}

void test_resize() {
    try {
        Image img("input.png");
        auto resized = resize(img, 100, 100);
        resized->save("output_resized.png");
        std::cout
            << "Resized image successfully and saved to output_resized.png."
            << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "test_resize failed: " << e.what() << std::endl;
    }
}

void test_rotate() {
    try {
        Image img("input.png");
        auto rotated = rotate(img);
        rotated->save("output_rotate.png");
        std::cout
            << "Rotated image successfully and saved to output_rotate.png."
            << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "test_rotate failed: " << e.what() << std::endl;
    }
}

void test_invert_colors() {
    try {
        Image img("input.png");
        invert_colors(img);
        img.save("output_invert_colors.png");
        std::cout
            << "Invert colors succeeded and saved to output_invert_colors.png."
            << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "test_invert_colors failed: " << e.what() << std::endl;
    }
}

int main() {
    try {
        test_load_image();
        test_save_image();
        test_flip_horizontal();
        test_flip_vertical();
        test_resize();
        test_rotate();
        test_invert_colors();
        std::cout << "All tests completed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error during tests: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
