cmake_minimum_required(VERSION 3.10)
project(ImageProcessingLib)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory to access header files
include_directories(include)

# Add source files to create a static library
add_library(image_processing STATIC src/Image.cpp src/Filters.cpp)

# Add the interactive application
add_executable(interactive_app src/interactive_app.cpp)
target_link_libraries(interactive_app image_processing)

# Add the test target
add_executable(test_image_processing test/test.cpp)
target_link_libraries(test_image_processing image_processing)
