# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.14.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.14.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/youssefhussein/programming/cplusplus/max_flow

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/youssefhussein/programming/cplusplus/max_flow/build

# Include any dependencies generated for this target.
include CMakeFiles/flow.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/flow.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/flow.dir/flags.make

CMakeFiles/flow.dir/main.cpp.o: CMakeFiles/flow.dir/flags.make
CMakeFiles/flow.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/youssefhussein/programming/cplusplus/max_flow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/flow.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/flow.dir/main.cpp.o -c /Users/youssefhussein/programming/cplusplus/max_flow/main.cpp

CMakeFiles/flow.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flow.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/youssefhussein/programming/cplusplus/max_flow/main.cpp > CMakeFiles/flow.dir/main.cpp.i

CMakeFiles/flow.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flow.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/youssefhussein/programming/cplusplus/max_flow/main.cpp -o CMakeFiles/flow.dir/main.cpp.s

# Object files for target flow
flow_OBJECTS = \
"CMakeFiles/flow.dir/main.cpp.o"

# External object files for target flow
flow_EXTERNAL_OBJECTS =

flow: CMakeFiles/flow.dir/main.cpp.o
flow: CMakeFiles/flow.dir/build.make
flow: CMakeFiles/flow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/youssefhussein/programming/cplusplus/max_flow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable flow"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/flow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/flow.dir/build: flow

.PHONY : CMakeFiles/flow.dir/build

CMakeFiles/flow.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/flow.dir/cmake_clean.cmake
.PHONY : CMakeFiles/flow.dir/clean

CMakeFiles/flow.dir/depend:
	cd /Users/youssefhussein/programming/cplusplus/max_flow/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/youssefhussein/programming/cplusplus/max_flow /Users/youssefhussein/programming/cplusplus/max_flow /Users/youssefhussein/programming/cplusplus/max_flow/build /Users/youssefhussein/programming/cplusplus/max_flow/build /Users/youssefhussein/programming/cplusplus/max_flow/build/CMakeFiles/flow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/flow.dir/depend
