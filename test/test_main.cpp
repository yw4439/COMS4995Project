#include <iostream>

#include "../include/Filters.hpp"
#include "../include/Image.hpp"

using namespace image_processing;

int main() {
    try {
        // Load a test image (Assume you have test_images/sample.png file)
        Image img("1.png");
        std::cout << "Image loaded successfully: " << img.getWidth() << "x"
                  << img.getHeight() << " with " << img.getChannels()
                  << " channels.\n";

        // Test grayscale conversion
        grayscale(img);
        std::cout << "Grayscale conversion applied successfully.\n";

        // Test horizontal flip
        flip_horizontal(img);
        std::cout << "Horizontal flip applied successfully.\n";

        // Test vertical flip
        flip_vertical(img);
        std::cout << "Vertical flip applied successfully.\n";

        // Test rotation
        Image rotated = rotate(img);
        std::cout << "Image rotated successfully.\n";

        // Test edge detection
        edge_detection(img);
        std::cout << "Edge detection applied successfully.\n";

        // Save the test result
        img.save("test_images/output.png");
        std::cout << "Image saved successfully as output.png.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
