#include <iostream>

#include "../include/Filters.hpp"
#include "../include/Image.hpp"

using namespace image_processing;

// int main() {
//     try {
//         // Load a test image (Assume you have test_images/sample.png file)
//         Image img;
//         if (!img.load("1.png")) {
//             std::cerr << "Failed to load PNG image!" << std::endl;
//             return 1;
//         }

//         // Test grayscale conversion
//         grayscale(img);
//         std::cout << "Grayscale conversion applied successfully.\n";

//         // Test horizontal flip
//         flip_horizontal(img);
//         std::cout << "Horizontal flip applied successfully.\n";

//         // Test vertical flip
//         flip_vertical(img);
//         std::cout << "Vertical flip applied successfully.\n";

//         // Test rotation
//         Image rotated = rotate(img);
//         std::cout << "Image rotated successfully.\n";

//         // Test edge detection
//         edge_detection(img);
//         std::cout << "Edge detection applied successfully.\n";

//         // Save the test result
//         if (!img.save("output.png")) {
//             std::cerr << "Failed to save PNG image!" << std::endl;
//             return 1;
//         }

//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }
int main() {
    Image img;
    if (!img.load("1.png")) {
        std::cerr << "Failed to load PNG image!" << std::endl;
        return 1;
    }

    try {
        // Rotate the image by 45 degrees
        rotate_image(img, 45.0f);

        // Save the rotated image
        img.save("output_rotated.png");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}