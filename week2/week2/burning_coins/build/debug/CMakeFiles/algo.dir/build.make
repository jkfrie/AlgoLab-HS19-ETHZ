# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins/build/debug

# Include any dependencies generated for this target.
include CMakeFiles/algo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/algo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/algo.dir/flags.make

CMakeFiles/algo.dir/src/algorithm.cpp.o: CMakeFiles/algo.dir/flags.make
CMakeFiles/algo.dir/src/algorithm.cpp.o: ../../src/algorithm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/algo.dir/src/algorithm.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/algo.dir/src/algorithm.cpp.o -c /home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins/src/algorithm.cpp

CMakeFiles/algo.dir/src/algorithm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/algo.dir/src/algorithm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins/src/algorithm.cpp > CMakeFiles/algo.dir/src/algorithm.cpp.i

CMakeFiles/algo.dir/src/algorithm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/algo.dir/src/algorithm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins/src/algorithm.cpp -o CMakeFiles/algo.dir/src/algorithm.cpp.s

CMakeFiles/algo.dir/src/algorithm.cpp.o.requires:

.PHONY : CMakeFiles/algo.dir/src/algorithm.cpp.o.requires

CMakeFiles/algo.dir/src/algorithm.cpp.o.provides: CMakeFiles/algo.dir/src/algorithm.cpp.o.requires
	$(MAKE) -f CMakeFiles/algo.dir/build.make CMakeFiles/algo.dir/src/algorithm.cpp.o.provides.build
.PHONY : CMakeFiles/algo.dir/src/algorithm.cpp.o.provides

CMakeFiles/algo.dir/src/algorithm.cpp.o.provides.build: CMakeFiles/algo.dir/src/algorithm.cpp.o


# Object files for target algo
algo_OBJECTS = \
"CMakeFiles/algo.dir/src/algorithm.cpp.o"

# External object files for target algo
algo_EXTERNAL_OBJECTS =

algo: CMakeFiles/algo.dir/src/algorithm.cpp.o
algo: CMakeFiles/algo.dir/build.make
algo: /usr/lib/x86_64-linux-gnu/libmpfr.so
algo: /usr/lib/x86_64-linux-gnu/libgmpxx.so
algo: /usr/lib/x86_64-linux-gnu/libgmp.so
algo: /usr/lib/x86_64-linux-gnu/libCGAL_Core.so.13.0.1
algo: /usr/lib/x86_64-linux-gnu/libCGAL.so.13.0.1
algo: /usr/lib/x86_64-linux-gnu/libboost_thread.so
algo: /usr/lib/x86_64-linux-gnu/libboost_system.so
algo: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
algo: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
algo: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
algo: /usr/lib/x86_64-linux-gnu/libpthread.so
algo: /usr/lib/x86_64-linux-gnu/libboost_thread.so
algo: /usr/lib/x86_64-linux-gnu/libboost_system.so
algo: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
algo: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
algo: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
algo: /usr/lib/x86_64-linux-gnu/libpthread.so
algo: /usr/lib/x86_64-linux-gnu/libCGAL_Core.so.13.0.1
algo: /usr/lib/x86_64-linux-gnu/libCGAL.so.13.0.1
algo: /usr/lib/x86_64-linux-gnu/libboost_thread.so
algo: /usr/lib/x86_64-linux-gnu/libboost_system.so
algo: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
algo: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
algo: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
algo: /usr/lib/x86_64-linux-gnu/libpthread.so
algo: /usr/lib/x86_64-linux-gnu/libmpfr.so
algo: /usr/lib/x86_64-linux-gnu/libgmp.so
algo: /usr/lib/x86_64-linux-gnu/libgmpxx.so
algo: CMakeFiles/algo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable algo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/algo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/algo.dir/build: algo

.PHONY : CMakeFiles/algo.dir/build

CMakeFiles/algo.dir/requires: CMakeFiles/algo.dir/src/algorithm.cpp.o.requires

.PHONY : CMakeFiles/algo.dir/requires

CMakeFiles/algo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/algo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/algo.dir/clean

CMakeFiles/algo.dir/depend:
	cd /home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins/build/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins /home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins /home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins/build/debug /home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins/build/debug /home/jasonf/Dokumente/AlgoLab-HS19-ETHZ/week2/week2/burning_coins/build/debug/CMakeFiles/algo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/algo.dir/depend

