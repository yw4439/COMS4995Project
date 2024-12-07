#include "Image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "stb_image_write.h"

namespace image_processing {

// Default constructor
Image::Image() : width(0), height(0), channels(0) {}

// Constructor with width, height, and channels
Image::Image(int w, int h, int c)
    : width(w), height(h), channels(c), data(w * h * c) {}

// Constructor with file path
Image::Image(const std::string& filepath) {
    if (!load(filepath)) {
        throw std::runtime_error("Failed to load image: " + filepath);
    }
}

// Copy constructor
Image::Image(const Image& other)
    : width(other.width),
      height(other.height),
      channels(other.channels),
      data(other.data) {}

// Copy assignment operator
Image& Image::operator=(const Image& other) {
    if (this != &other) {
        width    = other.width;
        height   = other.height;
        channels = other.channels;
        data     = other.data;
    }
    return *this;
}

// Move constructor
Image::Image(Image&& other) noexcept
    : width(std::exchange(other.width, 0)),
      height(std::exchange(other.height, 0)),
      channels(std::exchange(other.channels, 0)),
      data(std::move(other.data)) {}

// Move assignment operator
Image& Image::operator=(Image&& other) noexcept {
    if (this != &other) {
        width    = std::exchange(other.width, 0);
        height   = std::exchange(other.height, 0);
        channels = std::exchange(other.channels, 0);
        data     = std::move(other.data);
    }
    return *this;
}

bool Image::load(const std::string& filepath) {
    const auto extension = filepath.substr(filepath.find_last_of('.') + 1);
    if (extension == "png") {
        return loadPNG(filepath);
    } else if (extension == "bmp") {
        return loadBMP(filepath);
    } else {
        std::cerr << "Unsupported file format: " << filepath << std::endl;
        return false;
    }
}

bool Image::save(const std::string& filepath) const {
    const auto extension = filepath.substr(filepath.find_last_of('.') + 1);
    if (extension == "png") {
        return savePNG(filepath);
    } else if (extension == "bmp") {
        return saveBMP(filepath);
    } else {
        std::cerr << "Unsupported file format: " << filepath << std::endl;
        return false;
    }
}

bool Image::loadPNG(const std::string& filepath) {
    int w, h, c;
    std::unique_ptr<uint8_t, void (*)(void*)> pngData(
        stbi_load(filepath.c_str(), &w, &h, &c, 0), stbi_image_free);

    if (!pngData) {
        std::cerr << "Failed to load PNG file: " << filepath << std::endl;
        return false;
    }

    width    = w;
    height   = h;
    channels = c;
    data.assign(pngData.get(), pngData.get() + (width * height * channels));

    return true;
}

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

bool Image::loadBMP(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error: Could not open file: " + filepath);
    }

    std::array<uint8_t, 54> header;
    file.read(reinterpret_cast<char*>(header.data()), header.size());

    if (header[0] != 'B' || header[1] != 'M') {
        throw std::runtime_error("Error: Not a valid BMP file.");
    }

    width                 = *reinterpret_cast<int*>(&header[18]);
    height                = *reinterpret_cast<int*>(&header[22]);
    uint16_t bitsPerPixel = *reinterpret_cast<uint16_t*>(&header[28]);
    channels              = bitsPerPixel / 8;

    if (width <= 0 || height <= 0 || (channels != 3 && channels != 1)) {
        throw std::runtime_error(
            "Error: Invalid BMP dimensions or unsupported format.");
    }

    uint32_t dataOffset = *reinterpret_cast<uint32_t*>(&header[10]);
    file.seekg(dataOffset, std::ios::beg);

    data.resize(width * height * channels);
    file.read(reinterpret_cast<char*>(data.data()), data.size());

    return true;
}

bool Image::saveBMP(const std::string& filepath) const {
    std::ofstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error: Could not create file: " + filepath);
    }

    std::array<uint8_t, 54> header         = {};
    header[0]                              = 'B';
    header[1]                              = 'M';
    *reinterpret_cast<int*>(&header[2])    = 54 + data.size();
    *reinterpret_cast<int*>(&header[10])   = 54;
    *reinterpret_cast<int*>(&header[18])   = width;
    *reinterpret_cast<int*>(&header[22])   = height;
    *reinterpret_cast<short*>(&header[26]) = 1;
    *reinterpret_cast<short*>(&header[28]) = channels * 8;

    file.write(reinterpret_cast<const char*>(header.data()), header.size());
    file.write(reinterpret_cast<const char*>(data.data()), data.size());

    return true;
}

}  // namespace image_processing
