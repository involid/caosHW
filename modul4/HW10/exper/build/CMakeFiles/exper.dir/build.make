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
CMAKE_COMMAND = /var/lib/snapd/snap/cmake/1288/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/cmake/1288/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/involid/mhernoc/caosHW/modul4/HW10/exper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/involid/mhernoc/caosHW/modul4/HW10/exper/build

# Include any dependencies generated for this target.
include CMakeFiles/exper.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/exper.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/exper.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exper.dir/flags.make

CMakeFiles/exper.dir/exper.c.o: CMakeFiles/exper.dir/flags.make
CMakeFiles/exper.dir/exper.c.o: /home/involid/mhernoc/caosHW/modul4/HW10/exper/exper.c
CMakeFiles/exper.dir/exper.c.o: CMakeFiles/exper.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/involid/mhernoc/caosHW/modul4/HW10/exper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/exper.dir/exper.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/exper.dir/exper.c.o -MF CMakeFiles/exper.dir/exper.c.o.d -o CMakeFiles/exper.dir/exper.c.o -c /home/involid/mhernoc/caosHW/modul4/HW10/exper/exper.c

CMakeFiles/exper.dir/exper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/exper.dir/exper.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/involid/mhernoc/caosHW/modul4/HW10/exper/exper.c > CMakeFiles/exper.dir/exper.c.i

CMakeFiles/exper.dir/exper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/exper.dir/exper.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/involid/mhernoc/caosHW/modul4/HW10/exper/exper.c -o CMakeFiles/exper.dir/exper.c.s

# Object files for target exper
exper_OBJECTS = \
"CMakeFiles/exper.dir/exper.c.o"

# External object files for target exper
exper_EXTERNAL_OBJECTS =

exper: CMakeFiles/exper.dir/exper.c.o
exper: CMakeFiles/exper.dir/build.make
exper: CMakeFiles/exper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/involid/mhernoc/caosHW/modul4/HW10/exper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable exper"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exper.dir/build: exper
.PHONY : CMakeFiles/exper.dir/build

CMakeFiles/exper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exper.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exper.dir/clean

CMakeFiles/exper.dir/depend:
	cd /home/involid/mhernoc/caosHW/modul4/HW10/exper/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/involid/mhernoc/caosHW/modul4/HW10/exper /home/involid/mhernoc/caosHW/modul4/HW10/exper /home/involid/mhernoc/caosHW/modul4/HW10/exper/build /home/involid/mhernoc/caosHW/modul4/HW10/exper/build /home/involid/mhernoc/caosHW/modul4/HW10/exper/build/CMakeFiles/exper.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exper.dir/depend

