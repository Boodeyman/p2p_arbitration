# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /Users/Admin/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake

# The command to remove a file.
RM = /Users/Admin/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/p2p_arbitration_cpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/p2p_arbitration_cpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/p2p_arbitration_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p2p_arbitration_cpp.dir/flags.make

CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.o: CMakeFiles/p2p_arbitration_cpp.dir/flags.make
CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.o: /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp/binance_cpp.cpp
CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.o: CMakeFiles/p2p_arbitration_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.o -MF CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.o.d -o CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.o -c /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp/binance_cpp.cpp

CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp/binance_cpp.cpp > CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.i

CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp/binance_cpp.cpp -o CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.s

# Object files for target p2p_arbitration_cpp
p2p_arbitration_cpp_OBJECTS = \
"CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.o"

# External object files for target p2p_arbitration_cpp
p2p_arbitration_cpp_EXTERNAL_OBJECTS =

p2p_arbitration_cpp: CMakeFiles/p2p_arbitration_cpp.dir/binance_cpp.cpp.o
p2p_arbitration_cpp: CMakeFiles/p2p_arbitration_cpp.dir/build.make
p2p_arbitration_cpp: /Library/Developer/CommandLineTools/SDKs/MacOSX14.4.sdk/usr/lib/libcurl.tbd
p2p_arbitration_cpp: CMakeFiles/p2p_arbitration_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable p2p_arbitration_cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p2p_arbitration_cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p2p_arbitration_cpp.dir/build: p2p_arbitration_cpp
.PHONY : CMakeFiles/p2p_arbitration_cpp.dir/build

CMakeFiles/p2p_arbitration_cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/p2p_arbitration_cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/p2p_arbitration_cpp.dir/clean

CMakeFiles/p2p_arbitration_cpp.dir/depend:
	cd /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp/cmake-build-debug /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp/cmake-build-debug /Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_cpp/cmake-build-debug/CMakeFiles/p2p_arbitration_cpp.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/p2p_arbitration_cpp.dir/depend
