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
include CMakeFiles/STATIC.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/STATIC.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/STATIC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/STATIC.dir/flags.make

CMakeFiles/STATIC.dir/bigfloat.cpp.o: CMakeFiles/STATIC.dir/flags.make
CMakeFiles/STATIC.dir/bigfloat.cpp.o: /Users/timofejbulgakov/CLionProjects/bigfloat/bigfloat.cpp
CMakeFiles/STATIC.dir/bigfloat.cpp.o: CMakeFiles/STATIC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/STATIC.dir/bigfloat.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/STATIC.dir/bigfloat.cpp.o -MF CMakeFiles/STATIC.dir/bigfloat.cpp.o.d -o CMakeFiles/STATIC.dir/bigfloat.cpp.o -c /Users/timofejbulgakov/CLionProjects/bigfloat/bigfloat.cpp

CMakeFiles/STATIC.dir/bigfloat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/STATIC.dir/bigfloat.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/timofejbulgakov/CLionProjects/bigfloat/bigfloat.cpp > CMakeFiles/STATIC.dir/bigfloat.cpp.i

CMakeFiles/STATIC.dir/bigfloat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/STATIC.dir/bigfloat.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/timofejbulgakov/CLionProjects/bigfloat/bigfloat.cpp -o CMakeFiles/STATIC.dir/bigfloat.cpp.s

# Object files for target STATIC
STATIC_OBJECTS = \
"CMakeFiles/STATIC.dir/bigfloat.cpp.o"

# External object files for target STATIC
STATIC_EXTERNAL_OBJECTS =

libSTATIC.a: CMakeFiles/STATIC.dir/bigfloat.cpp.o
libSTATIC.a: CMakeFiles/STATIC.dir/build.make
libSTATIC.a: CMakeFiles/STATIC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libSTATIC.a"
	$(CMAKE_COMMAND) -P CMakeFiles/STATIC.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/STATIC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/STATIC.dir/build: libSTATIC.a
.PHONY : CMakeFiles/STATIC.dir/build

CMakeFiles/STATIC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/STATIC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/STATIC.dir/clean

CMakeFiles/STATIC.dir/depend:
	cd /Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/timofejbulgakov/CLionProjects/bigfloat /Users/timofejbulgakov/CLionProjects/bigfloat /Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug /Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug /Users/timofejbulgakov/CLionProjects/bigfloat/cmake-build-debug/CMakeFiles/STATIC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/STATIC.dir/depend

