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
CMAKE_SOURCE_DIR = /home/involid/mhernoc/caosHW/modul4/HW10/0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/involid/mhernoc/caosHW/modul4/HW10/0

# Include any dependencies generated for this target.
include CMakeFiles/simplefs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/simplefs.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/simplefs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simplefs.dir/flags.make

CMakeFiles/simplefs.dir/inf-II-10-0.c.o: CMakeFiles/simplefs.dir/flags.make
CMakeFiles/simplefs.dir/inf-II-10-0.c.o: inf-II-10-0.c
CMakeFiles/simplefs.dir/inf-II-10-0.c.o: CMakeFiles/simplefs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/involid/mhernoc/caosHW/modul4/HW10/0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/simplefs.dir/inf-II-10-0.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/simplefs.dir/inf-II-10-0.c.o -MF CMakeFiles/simplefs.dir/inf-II-10-0.c.o.d -o CMakeFiles/simplefs.dir/inf-II-10-0.c.o -c /home/involid/mhernoc/caosHW/modul4/HW10/0/inf-II-10-0.c

CMakeFiles/simplefs.dir/inf-II-10-0.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simplefs.dir/inf-II-10-0.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/involid/mhernoc/caosHW/modul4/HW10/0/inf-II-10-0.c > CMakeFiles/simplefs.dir/inf-II-10-0.c.i

CMakeFiles/simplefs.dir/inf-II-10-0.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simplefs.dir/inf-II-10-0.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/involid/mhernoc/caosHW/modul4/HW10/0/inf-II-10-0.c -o CMakeFiles/simplefs.dir/inf-II-10-0.c.s

# Object files for target simplefs
simplefs_OBJECTS = \
"CMakeFiles/simplefs.dir/inf-II-10-0.c.o"

# External object files for target simplefs
simplefs_EXTERNAL_OBJECTS =

simplefs: CMakeFiles/simplefs.dir/inf-II-10-0.c.o
simplefs: CMakeFiles/simplefs.dir/build.make
simplefs: CMakeFiles/simplefs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/involid/mhernoc/caosHW/modul4/HW10/0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable simplefs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simplefs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simplefs.dir/build: simplefs
.PHONY : CMakeFiles/simplefs.dir/build

CMakeFiles/simplefs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simplefs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simplefs.dir/clean

CMakeFiles/simplefs.dir/depend:
	cd /home/involid/mhernoc/caosHW/modul4/HW10/0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/involid/mhernoc/caosHW/modul4/HW10/0 /home/involid/mhernoc/caosHW/modul4/HW10/0 /home/involid/mhernoc/caosHW/modul4/HW10/0 /home/involid/mhernoc/caosHW/modul4/HW10/0 /home/involid/mhernoc/caosHW/modul4/HW10/0/CMakeFiles/simplefs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simplefs.dir/depend
