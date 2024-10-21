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
CMAKE_SOURCE_DIR = /root/miniob

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/miniob

# Include any dependencies generated for this target.
include unittest/observer/CMakeFiles/bplus_tree_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unittest/observer/CMakeFiles/bplus_tree_test.dir/compiler_depend.make

# Include the progress variables for this target.
include unittest/observer/CMakeFiles/bplus_tree_test.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/observer/CMakeFiles/bplus_tree_test.dir/flags.make

unittest/observer/CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.o: unittest/observer/CMakeFiles/bplus_tree_test.dir/flags.make
unittest/observer/CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.o: unittest/observer/bplus_tree_test.cpp
unittest/observer/CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.o: unittest/observer/CMakeFiles/bplus_tree_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/miniob/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/observer/CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.o"
	cd /root/miniob/unittest/observer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/observer/CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.o -MF CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.o.d -o CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.o -c /root/miniob/unittest/observer/bplus_tree_test.cpp

unittest/observer/CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.i"
	cd /root/miniob/unittest/observer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/miniob/unittest/observer/bplus_tree_test.cpp > CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.i

unittest/observer/CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.s"
	cd /root/miniob/unittest/observer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/miniob/unittest/observer/bplus_tree_test.cpp -o CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.s

# Object files for target bplus_tree_test
bplus_tree_test_OBJECTS = \
"CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.o"

# External object files for target bplus_tree_test
bplus_tree_test_EXTERNAL_OBJECTS =

bin/bplus_tree_test: unittest/observer/CMakeFiles/bplus_tree_test.dir/bplus_tree_test.cpp.o
bin/bplus_tree_test: unittest/observer/CMakeFiles/bplus_tree_test.dir/build.make
bin/bplus_tree_test: lib/libcommon.a
bin/bplus_tree_test: lib/libobserver.a
bin/bplus_tree_test: lib/libcommon.a
bin/bplus_tree_test: /usr/lib/x86_64-linux-gnu/libreadline.so
bin/bplus_tree_test: /usr/local/lib/libevent_pthreads.a
bin/bplus_tree_test: /usr/local/lib/libevent_core.a
bin/bplus_tree_test: unittest/observer/CMakeFiles/bplus_tree_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/miniob/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/bplus_tree_test"
	cd /root/miniob/unittest/observer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bplus_tree_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/observer/CMakeFiles/bplus_tree_test.dir/build: bin/bplus_tree_test
.PHONY : unittest/observer/CMakeFiles/bplus_tree_test.dir/build

unittest/observer/CMakeFiles/bplus_tree_test.dir/clean:
	cd /root/miniob/unittest/observer && $(CMAKE_COMMAND) -P CMakeFiles/bplus_tree_test.dir/cmake_clean.cmake
.PHONY : unittest/observer/CMakeFiles/bplus_tree_test.dir/clean

unittest/observer/CMakeFiles/bplus_tree_test.dir/depend:
	cd /root/miniob && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/miniob /root/miniob/unittest/observer /root/miniob /root/miniob/unittest/observer /root/miniob/unittest/observer/CMakeFiles/bplus_tree_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/observer/CMakeFiles/bplus_tree_test.dir/depend

