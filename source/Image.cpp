#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Image.hpp"
#include "stb_image_write.h"

// 构造函数
Image::Image(int w, int h, int c)
    : width(w), height(h), channels(c), data(w * h * c) {}

// 通用加载函数
bool Image::load(const std::string& filepath) {
  if (filepath.substr(filepath.find_last_of(".") + 1) == "png") {
    return loadPNG(filepath);
  } else if (filepath.substr(filepath.find_last_of(".") + 1) == "bmp") {
    return loadBMP(filepath);
  } else {
    std::cerr << "Unsupported file format: " << filepath << std::endl;
    return false;
  }
}

// 通用保存函数
bool Image::save(const std::string& filepath) const {
  if (filepath.substr(filepath.find_last_of(".") + 1) == "png") {
    return savePNG(filepath);
  } else if (filepath.substr(filepath.find_last_of(".") + 1) == "bmp") {
    return saveBMP(filepath);
  } else {
    std::cerr << "Unsupported file format: " << filepath << std::endl;
    return false;
  }
}

// 加载 PNG 文件
bool Image::loadPNG(const std::string& filepath) {
  int w, h, c;
  uint8_t* pngData = stbi_load(filepath.c_str(), &w, &h, &c, 0);

  if (!pngData) {
    std::cerr << "Failed to load PNG file: " << filepath << std::endl;
    return false;
  }

  width    = w;
  height   = h;
  channels = c;
  data.assign(pngData, pngData + (width * height * channels));
  stbi_image_free(pngData);

  return true;
}

// 保存 PNG 文件
bool Image::savePNG(const std::string& filepath) const {
  if (channels < 1 || channels > 4) {
    std::cerr << "Unsupported number of channels for PNG: " << channels
              << std::endl;
    return false;
  }

  if (!stbi_write_png(filepath.c_str(), width, height, channels, data.data(),
                      width * channels)) {
    std::cerr << "Failed to save PNG file: " << filepath << std::endl;
    return false;
  }
  return true;
}

// 加载 BMP 文件
bool Image::loadBMP(const std::string& filepath) {
  std::ifstream file(filepath, std::ios::binary);
  if (!file) {
    std::cerr << "Error: Could not open file: " << filepath << std::endl;
    return false;
  }

  uint8_t header[54];
  file.read(reinterpret_cast<char*>(header), 54);

  if (header[0] != 'B' || header[1] != 'M') {
    std::cerr << "Error: Not a valid BMP file." << std::endl;
    return false;
  }

  width                 = *reinterpret_cast<int*>(&header[18]);
  height                = *reinterpret_cast<int*>(&header[22]);
  uint16_t bitsPerPixel = *reinterpret_cast<uint16_t*>(&header[28]);
  channels              = bitsPerPixel / 8;

  if (width <= 0 || height <= 0 || (channels != 3 && channels != 1)) {
    std::cerr << "Error: Invalid BMP dimensions or unsupported format."
              << std::endl;
    return false;
  }

  uint32_t dataOffset = *reinterpret_cast<uint32_t*>(&header[10]);
  file.seekg(dataOffset, std::ios::beg);

  data.resize(width * height * channels);
  file.read(reinterpret_cast<char*>(data.data()), data.size());

  return true;
}

// 保存 BMP 文件
bool Image::saveBMP(const std::string& filepath) const {
  std::ofstream file(filepath, std::ios::binary);
  if (!file) return false;

  uint8_t header[54]                     = {0};
  header[0]                              = 'B';
  header[1]                              = 'M';
  *reinterpret_cast<int*>(&header[2])    = 54 + data.size();
  *reinterpret_cast<int*>(&header[10])   = 54;
  *reinterpret_cast<int*>(&header[18])   = width;
  *reinterpret_cast<int*>(&header[22])   = height;
  *reinterpret_cast<short*>(&header[26]) = 1;
  *reinterpret_cast<short*>(&header[28]) = channels * 8;

  file.write(reinterpret_cast<const char*>(header), 54);
  file.write(reinterpret_cast<const char*>(data.data()), data.size());

  return true;
}
