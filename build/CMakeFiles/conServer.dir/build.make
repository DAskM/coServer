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
include CMakeFiles/conServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/conServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/conServer.dir/flags.make

CMakeFiles/conServer.dir/src/log.cc.o: CMakeFiles/conServer.dir/flags.make
CMakeFiles/conServer.dir/src/log.cc.o: ../src/log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/conServer.dir/src/log.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conServer.dir/src/log.cc.o -c /home/leedong/Desktop/Project/conServer/src/log.cc

CMakeFiles/conServer.dir/src/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conServer.dir/src/log.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/log.cc > CMakeFiles/conServer.dir/src/log.cc.i

CMakeFiles/conServer.dir/src/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conServer.dir/src/log.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/log.cc -o CMakeFiles/conServer.dir/src/log.cc.s

CMakeFiles/conServer.dir/src/util.cc.o: CMakeFiles/conServer.dir/flags.make
CMakeFiles/conServer.dir/src/util.cc.o: ../src/util.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/conServer.dir/src/util.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conServer.dir/src/util.cc.o -c /home/leedong/Desktop/Project/conServer/src/util.cc

CMakeFiles/conServer.dir/src/util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conServer.dir/src/util.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/util.cc > CMakeFiles/conServer.dir/src/util.cc.i

CMakeFiles/conServer.dir/src/util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conServer.dir/src/util.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/util.cc -o CMakeFiles/conServer.dir/src/util.cc.s

CMakeFiles/conServer.dir/src/config.cc.o: CMakeFiles/conServer.dir/flags.make
CMakeFiles/conServer.dir/src/config.cc.o: ../src/config.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/conServer.dir/src/config.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conServer.dir/src/config.cc.o -c /home/leedong/Desktop/Project/conServer/src/config.cc

CMakeFiles/conServer.dir/src/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conServer.dir/src/config.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/config.cc > CMakeFiles/conServer.dir/src/config.cc.i

CMakeFiles/conServer.dir/src/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conServer.dir/src/config.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/config.cc -o CMakeFiles/conServer.dir/src/config.cc.s

CMakeFiles/conServer.dir/src/thread.cc.o: CMakeFiles/conServer.dir/flags.make
CMakeFiles/conServer.dir/src/thread.cc.o: ../src/thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/conServer.dir/src/thread.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conServer.dir/src/thread.cc.o -c /home/leedong/Desktop/Project/conServer/src/thread.cc

CMakeFiles/conServer.dir/src/thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conServer.dir/src/thread.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/thread.cc > CMakeFiles/conServer.dir/src/thread.cc.i

CMakeFiles/conServer.dir/src/thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conServer.dir/src/thread.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/thread.cc -o CMakeFiles/conServer.dir/src/thread.cc.s

CMakeFiles/conServer.dir/src/mutex.cc.o: CMakeFiles/conServer.dir/flags.make
CMakeFiles/conServer.dir/src/mutex.cc.o: ../src/mutex.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/conServer.dir/src/mutex.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conServer.dir/src/mutex.cc.o -c /home/leedong/Desktop/Project/conServer/src/mutex.cc

CMakeFiles/conServer.dir/src/mutex.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conServer.dir/src/mutex.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/mutex.cc > CMakeFiles/conServer.dir/src/mutex.cc.i

CMakeFiles/conServer.dir/src/mutex.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conServer.dir/src/mutex.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/mutex.cc -o CMakeFiles/conServer.dir/src/mutex.cc.s

CMakeFiles/conServer.dir/src/fiber.cc.o: CMakeFiles/conServer.dir/flags.make
CMakeFiles/conServer.dir/src/fiber.cc.o: ../src/fiber.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/conServer.dir/src/fiber.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conServer.dir/src/fiber.cc.o -c /home/leedong/Desktop/Project/conServer/src/fiber.cc

CMakeFiles/conServer.dir/src/fiber.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conServer.dir/src/fiber.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/fiber.cc > CMakeFiles/conServer.dir/src/fiber.cc.i

CMakeFiles/conServer.dir/src/fiber.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conServer.dir/src/fiber.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/fiber.cc -o CMakeFiles/conServer.dir/src/fiber.cc.s

CMakeFiles/conServer.dir/src/scheduler.cc.o: CMakeFiles/conServer.dir/flags.make
CMakeFiles/conServer.dir/src/scheduler.cc.o: ../src/scheduler.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/conServer.dir/src/scheduler.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conServer.dir/src/scheduler.cc.o -c /home/leedong/Desktop/Project/conServer/src/scheduler.cc

CMakeFiles/conServer.dir/src/scheduler.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conServer.dir/src/scheduler.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/scheduler.cc > CMakeFiles/conServer.dir/src/scheduler.cc.i

CMakeFiles/conServer.dir/src/scheduler.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conServer.dir/src/scheduler.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/scheduler.cc -o CMakeFiles/conServer.dir/src/scheduler.cc.s

CMakeFiles/conServer.dir/src/iomanager.cc.o: CMakeFiles/conServer.dir/flags.make
CMakeFiles/conServer.dir/src/iomanager.cc.o: ../src/iomanager.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/conServer.dir/src/iomanager.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conServer.dir/src/iomanager.cc.o -c /home/leedong/Desktop/Project/conServer/src/iomanager.cc

CMakeFiles/conServer.dir/src/iomanager.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conServer.dir/src/iomanager.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/iomanager.cc > CMakeFiles/conServer.dir/src/iomanager.cc.i

CMakeFiles/conServer.dir/src/iomanager.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conServer.dir/src/iomanager.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/iomanager.cc -o CMakeFiles/conServer.dir/src/iomanager.cc.s

CMakeFiles/conServer.dir/src/timer.cc.o: CMakeFiles/conServer.dir/flags.make
CMakeFiles/conServer.dir/src/timer.cc.o: ../src/timer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/conServer.dir/src/timer.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conServer.dir/src/timer.cc.o -c /home/leedong/Desktop/Project/conServer/src/timer.cc

CMakeFiles/conServer.dir/src/timer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conServer.dir/src/timer.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/timer.cc > CMakeFiles/conServer.dir/src/timer.cc.i

CMakeFiles/conServer.dir/src/timer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conServer.dir/src/timer.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/timer.cc -o CMakeFiles/conServer.dir/src/timer.cc.s

CMakeFiles/conServer.dir/src/fd_manager.cc.o: CMakeFiles/conServer.dir/flags.make
CMakeFiles/conServer.dir/src/fd_manager.cc.o: ../src/fd_manager.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/conServer.dir/src/fd_manager.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conServer.dir/src/fd_manager.cc.o -c /home/leedong/Desktop/Project/conServer/src/fd_manager.cc

CMakeFiles/conServer.dir/src/fd_manager.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conServer.dir/src/fd_manager.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/fd_manager.cc > CMakeFiles/conServer.dir/src/fd_manager.cc.i

CMakeFiles/conServer.dir/src/fd_manager.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conServer.dir/src/fd_manager.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/fd_manager.cc -o CMakeFiles/conServer.dir/src/fd_manager.cc.s

CMakeFiles/conServer.dir/src/hook.cc.o: CMakeFiles/conServer.dir/flags.make
CMakeFiles/conServer.dir/src/hook.cc.o: ../src/hook.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/conServer.dir/src/hook.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conServer.dir/src/hook.cc.o -c /home/leedong/Desktop/Project/conServer/src/hook.cc

CMakeFiles/conServer.dir/src/hook.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conServer.dir/src/hook.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leedong/Desktop/Project/conServer/src/hook.cc > CMakeFiles/conServer.dir/src/hook.cc.i

CMakeFiles/conServer.dir/src/hook.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conServer.dir/src/hook.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leedong/Desktop/Project/conServer/src/hook.cc -o CMakeFiles/conServer.dir/src/hook.cc.s

# Object files for target conServer
conServer_OBJECTS = \
"CMakeFiles/conServer.dir/src/log.cc.o" \
"CMakeFiles/conServer.dir/src/util.cc.o" \
"CMakeFiles/conServer.dir/src/config.cc.o" \
"CMakeFiles/conServer.dir/src/thread.cc.o" \
"CMakeFiles/conServer.dir/src/mutex.cc.o" \
"CMakeFiles/conServer.dir/src/fiber.cc.o" \
"CMakeFiles/conServer.dir/src/scheduler.cc.o" \
"CMakeFiles/conServer.dir/src/iomanager.cc.o" \
"CMakeFiles/conServer.dir/src/timer.cc.o" \
"CMakeFiles/conServer.dir/src/fd_manager.cc.o" \
"CMakeFiles/conServer.dir/src/hook.cc.o"

# External object files for target conServer
conServer_EXTERNAL_OBJECTS =

../lib/libconServer.so: CMakeFiles/conServer.dir/src/log.cc.o
../lib/libconServer.so: CMakeFiles/conServer.dir/src/util.cc.o
../lib/libconServer.so: CMakeFiles/conServer.dir/src/config.cc.o
../lib/libconServer.so: CMakeFiles/conServer.dir/src/thread.cc.o
../lib/libconServer.so: CMakeFiles/conServer.dir/src/mutex.cc.o
../lib/libconServer.so: CMakeFiles/conServer.dir/src/fiber.cc.o
../lib/libconServer.so: CMakeFiles/conServer.dir/src/scheduler.cc.o
../lib/libconServer.so: CMakeFiles/conServer.dir/src/iomanager.cc.o
../lib/libconServer.so: CMakeFiles/conServer.dir/src/timer.cc.o
../lib/libconServer.so: CMakeFiles/conServer.dir/src/fd_manager.cc.o
../lib/libconServer.so: CMakeFiles/conServer.dir/src/hook.cc.o
../lib/libconServer.so: CMakeFiles/conServer.dir/build.make
../lib/libconServer.so: CMakeFiles/conServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leedong/Desktop/Project/conServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX shared library ../lib/libconServer.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/conServer.dir/build: ../lib/libconServer.so

.PHONY : CMakeFiles/conServer.dir/build

CMakeFiles/conServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/conServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/conServer.dir/clean

CMakeFiles/conServer.dir/depend:
	cd /home/leedong/Desktop/Project/conServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leedong/Desktop/Project/conServer /home/leedong/Desktop/Project/conServer /home/leedong/Desktop/Project/conServer/build /home/leedong/Desktop/Project/conServer/build /home/leedong/Desktop/Project/conServer/build/CMakeFiles/conServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/conServer.dir/depend

