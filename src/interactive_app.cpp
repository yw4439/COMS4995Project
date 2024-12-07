#include <iostream>
#include <stdexcept>
#include <string>

#include "Filters.hpp"
#include "Image.hpp"

using namespace image_processing;

void showMenu() {
    std::cout << "\nImage Processing Application\n";
    std::cout << "1. Flip Horizontal\n";
    std::cout << "2. Flip Vertical\n";
    std::cout << "3. Resize Image\n";
    std::cout << "4. Invert Colors\n";
    std::cout << "5. Rotate 90 Degrees\n";
    std::cout << "6. Rotate Image by Angle\n";
    std::cout << "7. Adjust Brightness\n";
    std::cout << "8. Adjust Contrast\n";
    std::cout << "9. Grayscale\n";
    std::cout << "10. Sharpen\n";
    std::cout << "11. Edge Detection\n";
    std::cout << "12. Gaussian Blur\n";
    std::cout << "13. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    std::string inputPath, outputPath;
    std::cout << "Enter the input image file path: ";
    std::cin >> inputPath;

    try {
        Image img(inputPath);

        int choice;
        do {
            showMenu();
            std::cin >> choice;

            switch (choice) {
                case 1:
                    flip_horizontal(img);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    img.save(outputPath);
                    std::cout << "Image flipped horizontally and saved to "
                              << outputPath << "\n";
                    break;
                case 2:
                    flip_vertical(img);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    img.save(outputPath);
                    std::cout << "Image flipped vertically and saved to "
                              << outputPath << "\n";
                    break;
                case 3: {
                    int newWidth, newHeight;
                    std::cout << "Enter new width: ";
                    std::cin >> newWidth;
                    std::cout << "Enter new height: ";
                    std::cin >> newHeight;
                    auto resized = resize(img, newWidth, newHeight);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    resized->save(outputPath);
                    std::cout << "Image resized and saved to " << outputPath
                              << "\n";
                    break;
                }
                case 4:
                    invert_colors(img);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    img.save(outputPath);
                    std::cout << "Colors inverted and saved to " << outputPath
                              << "\n";
                    break;
                case 5: {
                    auto rotated = rotate(img);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    rotated->save(outputPath);
                    std::cout << "Image rotated 90 degrees and saved to "
                              << outputPath << "\n";
                    break;
                }
                case 6: {
                    float angle;
                    std::cout << "Enter rotation angle (in degrees): ";
                    std::cin >> angle;
                    rotate_image(img, angle);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    img.save(outputPath);
                    std::cout << "Image rotated and saved to " << outputPath
                              << "\n";
                    break;
                }
                case 7: {
                    int brightness;
                    std::cout
                        << "Enter brightness adjustment value (-255 to 255): ";
                    std::cin >> brightness;
                    adjust_brightness(img, brightness);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    img.save(outputPath);
                    std::cout << "Brightness adjusted and saved to "
                              << outputPath << "\n";
                    break;
                }
                case 8: {
                    float contrast;
                    std::cout << "Enter contrast adjustment value (e.g., 1.2 "
                                 "for 20% increase): ";
                    std::cin >> contrast;
                    adjust_contrast(img, contrast);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    img.save(outputPath);
                    std::cout << "Contrast adjusted and saved to " << outputPath
                              << "\n";
                    break;
                }
                case 9: {
                    Image output(img.getWidth(), img.getHeight(),
                                 img.getChannels());
                    grayscale(img, output);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    output.save(outputPath);
                    std::cout << "Grayscale applied and saved to " << outputPath
                              << "\n";
                    break;
                }
                case 10:
                    sharpen(img);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    img.save(outputPath);
                    std::cout << "Image sharpened and saved to " << outputPath
                              << "\n";
                    break;
                case 11:
                    edge_detection(img);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    img.save(outputPath);
                    std::cout << "Edge detection applied and saved to "
                              << outputPath << "\n";
                    break;
                case 12:
                    gaussian_blur(img);
                    std::cout << "Enter output file path: ";
                    std::cin >> outputPath;
                    img.save(outputPath);
                    std::cout << "Gaussian blur applied and saved to "
                              << outputPath << "\n";
                    break;
                case 13:
                    std::cout << "Exiting application.\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } while (choice != 13);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
