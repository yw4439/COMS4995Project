#ifndef FILTERS_HPP
#define FILTERS_HPP

#include "Image.hpp"

// 将 RGB 图像转换为灰度图
void grayscale(Image& img);

void flip_horizontal(Image& img);

// 垂直翻转
void flip_vertical(Image& img);

// 缩放图像
Image resize(const Image& img, int new_width, int new_height);

// 旋转图像（90° 顺时针）
Image rotate(const Image& img);

// 边缘检测
void edge_detection(Image& img);

// 高斯模糊
void gaussian_blur(Image& img);

#endif
