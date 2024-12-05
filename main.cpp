#include "Image.hpp"
#include "Filters.hpp"
#include <iostream>

int main() {
    // 创建图像对象并加载 PNG 文件
    Image img(0, 0, 0);
    if (!img.load("input.png")) {
        std::cerr << "Failed to load PNG image!" << std::endl;
        return 1;
    }

    // 应用灰度化滤镜
    try {
        grayscale(img);
        flip_horizontal(img);
        flip_vertical(img);

            // 测试缩放
        Image resized = resize(img, 128, 128);

            // 测试旋转
        Image rotated = rotate(img);

            // 测试边缘检测
        edge_detection(img);

            // 测试高斯模糊
        gaussian_blur(img);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    // 保存处理后的 PNG 文件
    if (!img.save("output.png")) {
        std::cerr << "Failed to save PNG image!" << std::endl;
        return 1;
    }

    std::cout << "PNG image processed successfully! Saved as output.png." << std::endl;
    return 0;
}

