# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

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
CMAKE_SOURCE_DIR = /home/gustavo/git/roboime-usb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gustavo/git/roboime-usb/build

# Include any dependencies generated for this target.
include CMakeFiles/simple.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/simple.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simple.dir/flags.make

CMakeFiles/simple.dir/src/main.cpp.o: CMakeFiles/simple.dir/flags.make
CMakeFiles/simple.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gustavo/git/roboime-usb/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/simple.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/simple.dir/src/main.cpp.o -c /home/gustavo/git/roboime-usb/src/main.cpp

CMakeFiles/simple.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gustavo/git/roboime-usb/src/main.cpp > CMakeFiles/simple.dir/src/main.cpp.i

CMakeFiles/simple.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gustavo/git/roboime-usb/src/main.cpp -o CMakeFiles/simple.dir/src/main.cpp.s

CMakeFiles/simple.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/simple.dir/src/main.cpp.o.requires

CMakeFiles/simple.dir/src/main.cpp.o.provides: CMakeFiles/simple.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/simple.dir/build.make CMakeFiles/simple.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/simple.dir/src/main.cpp.o.provides

CMakeFiles/simple.dir/src/main.cpp.o.provides.build: CMakeFiles/simple.dir/src/main.cpp.o

CMakeFiles/simple.dir/src/joystick.cc.o: CMakeFiles/simple.dir/flags.make
CMakeFiles/simple.dir/src/joystick.cc.o: ../src/joystick.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gustavo/git/roboime-usb/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/simple.dir/src/joystick.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/simple.dir/src/joystick.cc.o -c /home/gustavo/git/roboime-usb/src/joystick.cc

CMakeFiles/simple.dir/src/joystick.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple.dir/src/joystick.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gustavo/git/roboime-usb/src/joystick.cc > CMakeFiles/simple.dir/src/joystick.cc.i

CMakeFiles/simple.dir/src/joystick.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple.dir/src/joystick.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gustavo/git/roboime-usb/src/joystick.cc -o CMakeFiles/simple.dir/src/joystick.cc.s

CMakeFiles/simple.dir/src/joystick.cc.o.requires:
.PHONY : CMakeFiles/simple.dir/src/joystick.cc.o.requires

CMakeFiles/simple.dir/src/joystick.cc.o.provides: CMakeFiles/simple.dir/src/joystick.cc.o.requires
	$(MAKE) -f CMakeFiles/simple.dir/build.make CMakeFiles/simple.dir/src/joystick.cc.o.provides.build
.PHONY : CMakeFiles/simple.dir/src/joystick.cc.o.provides

CMakeFiles/simple.dir/src/joystick.cc.o.provides.build: CMakeFiles/simple.dir/src/joystick.cc.o

# Object files for target simple
simple_OBJECTS = \
"CMakeFiles/simple.dir/src/main.cpp.o" \
"CMakeFiles/simple.dir/src/joystick.cc.o"

# External object files for target simple
simple_EXTERNAL_OBJECTS =

simple: CMakeFiles/simple.dir/src/main.cpp.o
simple: CMakeFiles/simple.dir/src/joystick.cc.o
simple: CMakeFiles/simple.dir/build.make
simple: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
simple: CMakeFiles/simple.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable simple"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simple.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simple.dir/build: simple
.PHONY : CMakeFiles/simple.dir/build

CMakeFiles/simple.dir/requires: CMakeFiles/simple.dir/src/main.cpp.o.requires
CMakeFiles/simple.dir/requires: CMakeFiles/simple.dir/src/joystick.cc.o.requires
.PHONY : CMakeFiles/simple.dir/requires

CMakeFiles/simple.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simple.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simple.dir/clean

CMakeFiles/simple.dir/depend:
	cd /home/gustavo/git/roboime-usb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gustavo/git/roboime-usb /home/gustavo/git/roboime-usb /home/gustavo/git/roboime-usb/build /home/gustavo/git/roboime-usb/build /home/gustavo/git/roboime-usb/build/CMakeFiles/simple.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simple.dir/depend

