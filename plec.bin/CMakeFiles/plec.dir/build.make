# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/catardif/plec/plec

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/catardif/plec/plec.bin

# Include any dependencies generated for this target.
include CMakeFiles/plec.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/plec.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/plec.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/plec.dir/flags.make

CMakeFiles/plec.dir/plec.cpp.o: CMakeFiles/plec.dir/flags.make
CMakeFiles/plec.dir/plec.cpp.o: /home/catardif/plec/plec/plec.cpp
CMakeFiles/plec.dir/plec.cpp.o: CMakeFiles/plec.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/catardif/plec/plec.bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/plec.dir/plec.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/plec.dir/plec.cpp.o -MF CMakeFiles/plec.dir/plec.cpp.o.d -o CMakeFiles/plec.dir/plec.cpp.o -c /home/catardif/plec/plec/plec.cpp

CMakeFiles/plec.dir/plec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/plec.dir/plec.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/catardif/plec/plec/plec.cpp > CMakeFiles/plec.dir/plec.cpp.i

CMakeFiles/plec.dir/plec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/plec.dir/plec.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/catardif/plec/plec/plec.cpp -o CMakeFiles/plec.dir/plec.cpp.s

# Object files for target plec
plec_OBJECTS = \
"CMakeFiles/plec.dir/plec.cpp.o"

# External object files for target plec
plec_EXTERNAL_OBJECTS =

plec: CMakeFiles/plec.dir/plec.cpp.o
plec: CMakeFiles/plec.dir/build.make
plec: CMakeFiles/plec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/catardif/plec/plec.bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable plec"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/plec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/plec.dir/build: plec
.PHONY : CMakeFiles/plec.dir/build

CMakeFiles/plec.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/plec.dir/cmake_clean.cmake
.PHONY : CMakeFiles/plec.dir/clean

CMakeFiles/plec.dir/depend:
	cd /home/catardif/plec/plec.bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/catardif/plec/plec /home/catardif/plec/plec /home/catardif/plec/plec.bin /home/catardif/plec/plec.bin /home/catardif/plec/plec.bin/CMakeFiles/plec.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/plec.dir/depend

