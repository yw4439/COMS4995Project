#include "Image.hpp"
#include "Filters.hpp"
#include <iostream>

int main() {
    try {
        Image img(0, 0, 0);
        if (!img.load("1.png")) {
            std::cerr << "Failed to load image!" << std::endl;
            return -1;
        }

        // 应用灰度滤镜
        grayscale(img);

        // 保存图像
        if (!img.save("output.png")) {
            std::cerr << "Failed to save image!" << std::endl;
            return -1;
        }

        std::cout << "Test completed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}