# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/leedong/Desktop/Project/conServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leedong/Desktop/Project/conServer/build

# Include any dependencies generated for this target.
include CMakeFiles/coServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/coServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/coServer.dir/flags.make

CMakeFiles/coServer.dir/src/log.cc.o: CMakeFiles/coServer.dir/flags.make
CMakeFiles/coServer.dir/src/log.cc.o: ../src/log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/coServer.dir/src/log.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coServer.dir/src/log.cc.o -c /home/leedong/Desktop/Project/conServer/src/log.cc

CMakeFiles/coServer.dir/src/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coServer.dir/src/log.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/log.cc > CMakeFiles/coServer.dir/src/log.cc.i

CMakeFiles/coServer.dir/src/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coServer.dir/src/log.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/log.cc -o CMakeFiles/coServer.dir/src/log.cc.s

# Object files for target coServer
coServer_OBJECTS = \
"CMakeFiles/coServer.dir/src/log.cc.o"

# External object files for target coServer
coServer_EXTERNAL_OBJECTS =

../lib/libcoServer.so: CMakeFiles/coServer.dir/src/log.cc.o
../lib/libcoServer.so: CMakeFiles/coServer.dir/build.make
../lib/libcoServer.so: CMakeFiles/coServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../lib/libcoServer.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/coServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/coServer.dir/build: ../lib/libcoServer.so

.PHONY : CMakeFiles/coServer.dir/build

CMakeFiles/coServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/coServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/coServer.dir/clean

CMakeFiles/coServer.dir/depend:
	cd /home/leedong/Desktop/Project/conServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leedong/Desktop/Project/conServer /home/leedong/Desktop/Project/conServer /home/leedong/Desktop/Project/conServer/build /home/leedong/Desktop/Project/conServer/build /home/leedong/Desktop/Project/conServer/build/CMakeFiles/coServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/coServer.dir/depend
