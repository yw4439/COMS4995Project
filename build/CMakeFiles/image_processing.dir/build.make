# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yanming/COMS4995Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yanming/COMS4995Project/build

# Include any dependencies generated for this target.
include CMakeFiles/image_processing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/image_processing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/image_processing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/image_processing.dir/flags.make

CMakeFiles/image_processing.dir/src/Image.cpp.o: CMakeFiles/image_processing.dir/flags.make
CMakeFiles/image_processing.dir/src/Image.cpp.o: /home/yanming/COMS4995Project/src/Image.cpp
CMakeFiles/image_processing.dir/src/Image.cpp.o: CMakeFiles/image_processing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yanming/COMS4995Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/image_processing.dir/src/Image.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image_processing.dir/src/Image.cpp.o -MF CMakeFiles/image_processing.dir/src/Image.cpp.o.d -o CMakeFiles/image_processing.dir/src/Image.cpp.o -c /home/yanming/COMS4995Project/src/Image.cpp

CMakeFiles/image_processing.dir/src/Image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/image_processing.dir/src/Image.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yanming/COMS4995Project/src/Image.cpp > CMakeFiles/image_processing.dir/src/Image.cpp.i

CMakeFiles/image_processing.dir/src/Image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/image_processing.dir/src/Image.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yanming/COMS4995Project/src/Image.cpp -o CMakeFiles/image_processing.dir/src/Image.cpp.s

CMakeFiles/image_processing.dir/src/Filters.cpp.o: CMakeFiles/image_processing.dir/flags.make
CMakeFiles/image_processing.dir/src/Filters.cpp.o: /home/yanming/COMS4995Project/src/Filters.cpp
CMakeFiles/image_processing.dir/src/Filters.cpp.o: CMakeFiles/image_processing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yanming/COMS4995Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/image_processing.dir/src/Filters.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image_processing.dir/src/Filters.cpp.o -MF CMakeFiles/image_processing.dir/src/Filters.cpp.o.d -o CMakeFiles/image_processing.dir/src/Filters.cpp.o -c /home/yanming/COMS4995Project/src/Filters.cpp

CMakeFiles/image_processing.dir/src/Filters.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/image_processing.dir/src/Filters.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yanming/COMS4995Project/src/Filters.cpp > CMakeFiles/image_processing.dir/src/Filters.cpp.i

CMakeFiles/image_processing.dir/src/Filters.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/image_processing.dir/src/Filters.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yanming/COMS4995Project/src/Filters.cpp -o CMakeFiles/image_processing.dir/src/Filters.cpp.s

# Object files for target image_processing
image_processing_OBJECTS = \
"CMakeFiles/image_processing.dir/src/Image.cpp.o" \
"CMakeFiles/image_processing.dir/src/Filters.cpp.o"

# External object files for target image_processing
image_processing_EXTERNAL_OBJECTS =

libimage_processing.a: CMakeFiles/image_processing.dir/src/Image.cpp.o
libimage_processing.a: CMakeFiles/image_processing.dir/src/Filters.cpp.o
libimage_processing.a: CMakeFiles/image_processing.dir/build.make
libimage_processing.a: CMakeFiles/image_processing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/yanming/COMS4995Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libimage_processing.a"
	$(CMAKE_COMMAND) -P CMakeFiles/image_processing.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/image_processing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/image_processing.dir/build: libimage_processing.a
.PHONY : CMakeFiles/image_processing.dir/build

CMakeFiles/image_processing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/image_processing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/image_processing.dir/clean

CMakeFiles/image_processing.dir/depend:
	cd /home/yanming/COMS4995Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yanming/COMS4995Project /home/yanming/COMS4995Project /home/yanming/COMS4995Project/build /home/yanming/COMS4995Project/build /home/yanming/COMS4995Project/build/CMakeFiles/image_processing.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/image_processing.dir/depend

