# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/timofejbulgakov/CLionProjects/bigfloat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bigfloat.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bigfloat.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bigfloat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bigfloat.dir/flags.make

CMakeFiles/bigfloat.dir/bigfloat.cpp.o: CMakeFiles/bigfloat.dir/flags.make
CMakeFiles/bigfloat.dir/bigfloat.cpp.o: /Users/timofejbulgakov/CLionProjects/bigfloat/bigfloat.cpp
CMakeFiles/bigfloat.dir/bigfloat.cpp.o: CMakeFiles/bigfloat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bigfloat.dir/bigfloat.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bigfloat.dir/bigfloat.cpp.o -MF CMakeFiles/bigfloat.dir/bigfloat.cpp.o.d -o CMakeFiles/bigfloat.dir/bigfloat.cpp.o -c /Users/timofejbulgakov/CLionProjects/bigfloat/bigfloat.cpp

CMakeFiles/bigfloat.dir/bigfloat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bigfloat.dir/bigfloat.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/timofejbulgakov/CLionProjects/bigfloat/bigfloat.cpp > CMakeFiles/bigfloat.dir/bigfloat.cpp.i

CMakeFiles/bigfloat.dir/bigfloat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bigfloat.dir/bigfloat.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/timofejbulgakov/CLionProjects/bigfloat/bigfloat.cpp -o CMakeFiles/bigfloat.dir/bigfloat.cpp.s

# Object files for target bigfloat
bigfloat_OBJECTS = \
"CMakeFiles/bigfloat.dir/bigfloat.cpp.o"

# External object files for target bigfloat
bigfloat_EXTERNAL_OBJECTS =

libbigfloat.a: CMakeFiles/bigfloat.dir/bigfloat.cpp.o
libbigfloat.a: CMakeFiles/bigfloat.dir/build.make
libbigfloat.a: CMakeFiles/bigfloat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libbigfloat.a"
	$(CMAKE_COMMAND) -P CMakeFiles/bigfloat.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bigfloat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bigfloat.dir/build: libbigfloat.a
.PHONY : CMakeFiles/bigfloat.dir/build

CMakeFiles/bigfloat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bigfloat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bigfloat.dir/clean

CMakeFiles/bigfloat.dir/depend:
	cd /Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/timofejbulgakov/CLionProjects/bigfloat /Users/timofejbulgakov/CLionProjects/bigfloat /Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug /Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug /Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug/CMakeFiles/bigfloat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bigfloat.dir/depend

