# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/tee/Desktop/Projects/c++/cubic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tee/Desktop/Projects/c++/cubic

# Include any dependencies generated for this target.
include CMakeFiles/Cubic_.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Cubic_.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Cubic_.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Cubic_.dir/flags.make

CMakeFiles/Cubic_.dir/main.cpp.o: CMakeFiles/Cubic_.dir/flags.make
CMakeFiles/Cubic_.dir/main.cpp.o: main.cpp
CMakeFiles/Cubic_.dir/main.cpp.o: CMakeFiles/Cubic_.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tee/Desktop/Projects/c++/cubic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Cubic_.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Cubic_.dir/main.cpp.o -MF CMakeFiles/Cubic_.dir/main.cpp.o.d -o CMakeFiles/Cubic_.dir/main.cpp.o -c /home/tee/Desktop/Projects/c++/cubic/main.cpp

CMakeFiles/Cubic_.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cubic_.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tee/Desktop/Projects/c++/cubic/main.cpp > CMakeFiles/Cubic_.dir/main.cpp.i

CMakeFiles/Cubic_.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cubic_.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tee/Desktop/Projects/c++/cubic/main.cpp -o CMakeFiles/Cubic_.dir/main.cpp.s

# Object files for target Cubic_
Cubic__OBJECTS = \
"CMakeFiles/Cubic_.dir/main.cpp.o"

# External object files for target Cubic_
Cubic__EXTERNAL_OBJECTS =

Cubic_: CMakeFiles/Cubic_.dir/main.cpp.o
Cubic_: CMakeFiles/Cubic_.dir/build.make
Cubic_: CMakeFiles/Cubic_.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tee/Desktop/Projects/c++/cubic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Cubic_"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Cubic_.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Cubic_.dir/build: Cubic_
.PHONY : CMakeFiles/Cubic_.dir/build

CMakeFiles/Cubic_.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Cubic_.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Cubic_.dir/clean

CMakeFiles/Cubic_.dir/depend:
	cd /home/tee/Desktop/Projects/c++/cubic && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tee/Desktop/Projects/c++/cubic /home/tee/Desktop/Projects/c++/cubic /home/tee/Desktop/Projects/c++/cubic /home/tee/Desktop/Projects/c++/cubic /home/tee/Desktop/Projects/c++/cubic/CMakeFiles/Cubic_.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Cubic_.dir/depend

