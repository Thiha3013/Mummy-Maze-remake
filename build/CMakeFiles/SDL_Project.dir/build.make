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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/tha/coding/projects/Mummy Maze"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/tha/coding/projects/Mummy Maze/build"

# Include any dependencies generated for this target.
include CMakeFiles/SDL_Project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SDL_Project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SDL_Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SDL_Project.dir/flags.make

CMakeFiles/SDL_Project.dir/src/game.cpp.o: CMakeFiles/SDL_Project.dir/flags.make
CMakeFiles/SDL_Project.dir/src/game.cpp.o: /Users/tha/coding/projects/Mummy\ Maze/src/game.cpp
CMakeFiles/SDL_Project.dir/src/game.cpp.o: CMakeFiles/SDL_Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/tha/coding/projects/Mummy Maze/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SDL_Project.dir/src/game.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SDL_Project.dir/src/game.cpp.o -MF CMakeFiles/SDL_Project.dir/src/game.cpp.o.d -o CMakeFiles/SDL_Project.dir/src/game.cpp.o -c "/Users/tha/coding/projects/Mummy Maze/src/game.cpp"

CMakeFiles/SDL_Project.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SDL_Project.dir/src/game.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tha/coding/projects/Mummy Maze/src/game.cpp" > CMakeFiles/SDL_Project.dir/src/game.cpp.i

CMakeFiles/SDL_Project.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SDL_Project.dir/src/game.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tha/coding/projects/Mummy Maze/src/game.cpp" -o CMakeFiles/SDL_Project.dir/src/game.cpp.s

CMakeFiles/SDL_Project.dir/src/main.cpp.o: CMakeFiles/SDL_Project.dir/flags.make
CMakeFiles/SDL_Project.dir/src/main.cpp.o: /Users/tha/coding/projects/Mummy\ Maze/src/main.cpp
CMakeFiles/SDL_Project.dir/src/main.cpp.o: CMakeFiles/SDL_Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/tha/coding/projects/Mummy Maze/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SDL_Project.dir/src/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SDL_Project.dir/src/main.cpp.o -MF CMakeFiles/SDL_Project.dir/src/main.cpp.o.d -o CMakeFiles/SDL_Project.dir/src/main.cpp.o -c "/Users/tha/coding/projects/Mummy Maze/src/main.cpp"

CMakeFiles/SDL_Project.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SDL_Project.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tha/coding/projects/Mummy Maze/src/main.cpp" > CMakeFiles/SDL_Project.dir/src/main.cpp.i

CMakeFiles/SDL_Project.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SDL_Project.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tha/coding/projects/Mummy Maze/src/main.cpp" -o CMakeFiles/SDL_Project.dir/src/main.cpp.s

CMakeFiles/SDL_Project.dir/src/utils.cpp.o: CMakeFiles/SDL_Project.dir/flags.make
CMakeFiles/SDL_Project.dir/src/utils.cpp.o: /Users/tha/coding/projects/Mummy\ Maze/src/utils.cpp
CMakeFiles/SDL_Project.dir/src/utils.cpp.o: CMakeFiles/SDL_Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/tha/coding/projects/Mummy Maze/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SDL_Project.dir/src/utils.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SDL_Project.dir/src/utils.cpp.o -MF CMakeFiles/SDL_Project.dir/src/utils.cpp.o.d -o CMakeFiles/SDL_Project.dir/src/utils.cpp.o -c "/Users/tha/coding/projects/Mummy Maze/src/utils.cpp"

CMakeFiles/SDL_Project.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SDL_Project.dir/src/utils.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tha/coding/projects/Mummy Maze/src/utils.cpp" > CMakeFiles/SDL_Project.dir/src/utils.cpp.i

CMakeFiles/SDL_Project.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SDL_Project.dir/src/utils.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tha/coding/projects/Mummy Maze/src/utils.cpp" -o CMakeFiles/SDL_Project.dir/src/utils.cpp.s

# Object files for target SDL_Project
SDL_Project_OBJECTS = \
"CMakeFiles/SDL_Project.dir/src/game.cpp.o" \
"CMakeFiles/SDL_Project.dir/src/main.cpp.o" \
"CMakeFiles/SDL_Project.dir/src/utils.cpp.o"

# External object files for target SDL_Project
SDL_Project_EXTERNAL_OBJECTS =

SDL_Project: CMakeFiles/SDL_Project.dir/src/game.cpp.o
SDL_Project: CMakeFiles/SDL_Project.dir/src/main.cpp.o
SDL_Project: CMakeFiles/SDL_Project.dir/src/utils.cpp.o
SDL_Project: CMakeFiles/SDL_Project.dir/build.make
SDL_Project: CMakeFiles/SDL_Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/tha/coding/projects/Mummy Maze/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable SDL_Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SDL_Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SDL_Project.dir/build: SDL_Project
.PHONY : CMakeFiles/SDL_Project.dir/build

CMakeFiles/SDL_Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SDL_Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SDL_Project.dir/clean

CMakeFiles/SDL_Project.dir/depend:
	cd "/Users/tha/coding/projects/Mummy Maze/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/tha/coding/projects/Mummy Maze" "/Users/tha/coding/projects/Mummy Maze" "/Users/tha/coding/projects/Mummy Maze/build" "/Users/tha/coding/projects/Mummy Maze/build" "/Users/tha/coding/projects/Mummy Maze/build/CMakeFiles/SDL_Project.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/SDL_Project.dir/depend

