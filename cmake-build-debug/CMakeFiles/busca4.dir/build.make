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
CMAKE_COMMAND = /snap/clion/250/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/250/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/patrick/Desktop/Projects/casalCiumento

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/patrick/Desktop/Projects/casalCiumento/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/busca4.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/busca4.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/busca4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/busca4.dir/flags.make

CMakeFiles/busca4.dir/BuscaProfundidade.cpp.o: CMakeFiles/busca4.dir/flags.make
CMakeFiles/busca4.dir/BuscaProfundidade.cpp.o: /home/patrick/Desktop/Projects/casalCiumento/BuscaProfundidade.cpp
CMakeFiles/busca4.dir/BuscaProfundidade.cpp.o: CMakeFiles/busca4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/Desktop/Projects/casalCiumento/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/busca4.dir/BuscaProfundidade.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/busca4.dir/BuscaProfundidade.cpp.o -MF CMakeFiles/busca4.dir/BuscaProfundidade.cpp.o.d -o CMakeFiles/busca4.dir/BuscaProfundidade.cpp.o -c /home/patrick/Desktop/Projects/casalCiumento/BuscaProfundidade.cpp

CMakeFiles/busca4.dir/BuscaProfundidade.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/busca4.dir/BuscaProfundidade.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/Desktop/Projects/casalCiumento/BuscaProfundidade.cpp > CMakeFiles/busca4.dir/BuscaProfundidade.cpp.i

CMakeFiles/busca4.dir/BuscaProfundidade.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/busca4.dir/BuscaProfundidade.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/Desktop/Projects/casalCiumento/BuscaProfundidade.cpp -o CMakeFiles/busca4.dir/BuscaProfundidade.cpp.s

# Object files for target busca4
busca4_OBJECTS = \
"CMakeFiles/busca4.dir/BuscaProfundidade.cpp.o"

# External object files for target busca4
busca4_EXTERNAL_OBJECTS =

busca4: CMakeFiles/busca4.dir/BuscaProfundidade.cpp.o
busca4: CMakeFiles/busca4.dir/build.make
busca4: libcasal.a
busca4: CMakeFiles/busca4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/patrick/Desktop/Projects/casalCiumento/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable busca4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/busca4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/busca4.dir/build: busca4
.PHONY : CMakeFiles/busca4.dir/build

CMakeFiles/busca4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/busca4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/busca4.dir/clean

CMakeFiles/busca4.dir/depend:
	cd /home/patrick/Desktop/Projects/casalCiumento/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/patrick/Desktop/Projects/casalCiumento /home/patrick/Desktop/Projects/casalCiumento /home/patrick/Desktop/Projects/casalCiumento/cmake-build-debug /home/patrick/Desktop/Projects/casalCiumento/cmake-build-debug /home/patrick/Desktop/Projects/casalCiumento/cmake-build-debug/CMakeFiles/busca4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/busca4.dir/depend

