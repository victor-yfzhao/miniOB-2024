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
include test/perf/CMakeFiles/client_performance_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/perf/CMakeFiles/client_performance_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/perf/CMakeFiles/client_performance_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/perf/CMakeFiles/client_performance_test.dir/flags.make

test/perf/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o: test/perf/CMakeFiles/client_performance_test.dir/flags.make
test/perf/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o: test/perf/client_performance_test.cpp
test/perf/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o: test/perf/CMakeFiles/client_performance_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/miniob/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/perf/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o"
	cd /root/miniob/test/perf && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/perf/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o -MF CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o.d -o CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o -c /root/miniob/test/perf/client_performance_test.cpp

test/perf/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_performance_test.dir/client_performance_test.cpp.i"
	cd /root/miniob/test/perf && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/miniob/test/perf/client_performance_test.cpp > CMakeFiles/client_performance_test.dir/client_performance_test.cpp.i

test/perf/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_performance_test.dir/client_performance_test.cpp.s"
	cd /root/miniob/test/perf && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/miniob/test/perf/client_performance_test.cpp -o CMakeFiles/client_performance_test.dir/client_performance_test.cpp.s

# Object files for target client_performance_test
client_performance_test_OBJECTS = \
"CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o"

# External object files for target client_performance_test
client_performance_test_EXTERNAL_OBJECTS =

bin/client_performance_test: test/perf/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o
bin/client_performance_test: test/perf/CMakeFiles/client_performance_test.dir/build.make
bin/client_performance_test: lib/libcommon.a
bin/client_performance_test: lib/libobserver.a
bin/client_performance_test: lib/libcommon.a
bin/client_performance_test: /usr/lib/x86_64-linux-gnu/libreadline.so
bin/client_performance_test: /usr/local/lib/libevent_pthreads.a
bin/client_performance_test: /usr/local/lib/libevent_core.a
bin/client_performance_test: test/perf/CMakeFiles/client_performance_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/miniob/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/client_performance_test"
	cd /root/miniob/test/perf && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_performance_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/perf/CMakeFiles/client_performance_test.dir/build: bin/client_performance_test
.PHONY : test/perf/CMakeFiles/client_performance_test.dir/build

test/perf/CMakeFiles/client_performance_test.dir/clean:
	cd /root/miniob/test/perf && $(CMAKE_COMMAND) -P CMakeFiles/client_performance_test.dir/cmake_clean.cmake
.PHONY : test/perf/CMakeFiles/client_performance_test.dir/clean

test/perf/CMakeFiles/client_performance_test.dir/depend:
	cd /root/miniob && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/miniob /root/miniob/test/perf /root/miniob /root/miniob/test/perf /root/miniob/test/perf/CMakeFiles/client_performance_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/perf/CMakeFiles/client_performance_test.dir/depend

