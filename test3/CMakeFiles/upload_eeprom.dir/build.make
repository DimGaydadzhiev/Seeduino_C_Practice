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

# Utility rule file for upload_eeprom.

# Include the progress variables for this target.
include CMakeFiles/upload_eeprom.dir/progress.make

CMakeFiles/upload_eeprom:
	avrdude -c arduino -P /dev/ttyUSB0 -p atmega328p -U eeprom:w:blinkTest.eep

upload_eeprom: CMakeFiles/upload_eeprom
upload_eeprom: CMakeFiles/upload_eeprom.dir/build.make

.PHONY : upload_eeprom

# Rule to build all files generated by this target.
CMakeFiles/upload_eeprom.dir/build: upload_eeprom

.PHONY : CMakeFiles/upload_eeprom.dir/build

CMakeFiles/upload_eeprom.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/upload_eeprom.dir/cmake_clean.cmake
.PHONY : CMakeFiles/upload_eeprom.dir/clean

CMakeFiles/upload_eeprom.dir/depend:
	cd /home/dimitar/Documents/project1/test3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dimitar/Documents/project1/test3 /home/dimitar/Documents/project1/test3 /home/dimitar/Documents/project1/test3 /home/dimitar/Documents/project1/test3 /home/dimitar/Documents/project1/test3/CMakeFiles/upload_eeprom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/upload_eeprom.dir/depend

