cmake_minimum_required(VERSION 3.10)
project(ImageProcessingLib)

# 设置 C++ 版本
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件路径
include_directories(${CMAKE_SOURCE_DIR}/include)

# 添加库
add_library(ImageProcessingLib STATIC
    source/Image.cpp
    source/Filters.cpp
)

# 测试（可选）
enable_testing()
add_executable(test_main test/test_main.cpp)
target_link_libraries(test_main ImageProcessingLib)
