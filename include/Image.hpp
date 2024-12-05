#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <string>
#include <cstdint>

class Image {
public:
    int width, height, channels;        // 图像宽度、高度、通道数
    std::vector<uint8_t> data;          // 像素数据

    // 构造函数
    Image(int w, int h, int c);

    // 加载和保存图像（支持 PNG 和 BMP）
    bool load(const std::string& filepath);
    bool save(const std::string& filepath) const;

private:
    bool loadBMP(const std::string& filepath); // 加载 BMP 文件
    bool saveBMP(const std::string& filepath) const; // 保存 BMP 文件
    bool loadPNG(const std::string& filepath); // 加载 PNG 文件
    bool savePNG(const std::string& filepath) const; // 保存 PNG 文件
};

#endif

