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
CMAKE_SOURCE_DIR = /home/dimitar/Documents/project1/test3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dimitar/Documents/project1/test3

# Include any dependencies generated for this target.
include CMakeFiles/blinkTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/blinkTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/blinkTest.dir/flags.make

CMakeFiles/blinkTest.dir/src/hal.c.o: CMakeFiles/blinkTest.dir/flags.make
CMakeFiles/blinkTest.dir/src/hal.c.o: src/hal.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimitar/Documents/project1/test3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/blinkTest.dir/src/hal.c.o"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/blinkTest.dir/src/hal.c.o   -c /home/dimitar/Documents/project1/test3/src/hal.c

CMakeFiles/blinkTest.dir/src/hal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/blinkTest.dir/src/hal.c.i"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dimitar/Documents/project1/test3/src/hal.c > CMakeFiles/blinkTest.dir/src/hal.c.i

CMakeFiles/blinkTest.dir/src/hal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/blinkTest.dir/src/hal.c.s"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dimitar/Documents/project1/test3/src/hal.c -o CMakeFiles/blinkTest.dir/src/hal.c.s

CMakeFiles/blinkTest.dir/src/main.c.o: CMakeFiles/blinkTest.dir/flags.make
CMakeFiles/blinkTest.dir/src/main.c.o: src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimitar/Documents/project1/test3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/blinkTest.dir/src/main.c.o"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/blinkTest.dir/src/main.c.o   -c /home/dimitar/Documents/project1/test3/src/main.c

CMakeFiles/blinkTest.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/blinkTest.dir/src/main.c.i"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dimitar/Documents/project1/test3/src/main.c > CMakeFiles/blinkTest.dir/src/main.c.i

CMakeFiles/blinkTest.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/blinkTest.dir/src/main.c.s"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dimitar/Documents/project1/test3/src/main.c -o CMakeFiles/blinkTest.dir/src/main.c.s

# Object files for target blinkTest
blinkTest_OBJECTS = \
"CMakeFiles/blinkTest.dir/src/hal.c.o" \
"CMakeFiles/blinkTest.dir/src/main.c.o"

# External object files for target blinkTest
blinkTest_EXTERNAL_OBJECTS =

blinkTest.elf: CMakeFiles/blinkTest.dir/src/hal.c.o
blinkTest.elf: CMakeFiles/blinkTest.dir/src/main.c.o
blinkTest.elf: CMakeFiles/blinkTest.dir/build.make
blinkTest.elf: CMakeFiles/blinkTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dimitar/Documents/project1/test3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable blinkTest.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/blinkTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/blinkTest.dir/build: blinkTest.elf

.PHONY : CMakeFiles/blinkTest.dir/build

CMakeFiles/blinkTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/blinkTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/blinkTest.dir/clean

CMakeFiles/blinkTest.dir/depend:
	cd /home/dimitar/Documents/project1/test3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dimitar/Documents/project1/test3 /home/dimitar/Documents/project1/test3 /home/dimitar/Documents/project1/test3 /home/dimitar/Documents/project1/test3 /home/dimitar/Documents/project1/test3/CMakeFiles/blinkTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/blinkTest.dir/depend

