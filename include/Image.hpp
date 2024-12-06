#pragma once

#include <memory>
#include <string>
#include <vector>

namespace image_processing {

class Image {
   public:
    Image();                     // Default constructor
    Image(int w, int h, int c);  // Constructor with width, height, and channels
    explicit Image(const std::string& filepath);  // Constructor with file path

    bool load(const std::string& filepath);
    bool save(const std::string& filepath) const;

    int getWidth() const noexcept { return width; }
    int getHeight() const noexcept { return height; }
    int getChannels() const noexcept { return channels; }

    std::vector<uint8_t>& getData() noexcept { return data; }
    const std::vector<uint8_t>& getData() const noexcept { return data; }

    // Copy and move constructors
    Image(const Image& other);      // Copy constructor
    Image(Image&& other) noexcept;  // Move constructor

    // Copy and move assignment operators
    Image& operator=(const Image& other);      // Copy assignment operator
    Image& operator=(Image&& other) noexcept;  // Move assignment operator

   private:
    int width;
    int height;
    int channels;
    std::vector<uint8_t> data;

    bool loadPNG(const std::string& filepath);
    bool savePNG(const std::string& filepath) const;
    bool loadBMP(const std::string& filepath);
    bool saveBMP(const std::string& filepath) const;
};

}  // namespace image_processing
