# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Administrator\Documents\VASIKARAN\Monolithic project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Administrator\Documents\VASIKARAN\Monolithic project\build"

# Include any dependencies generated for this target.
include CMakeFiles/TceLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TceLib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TceLib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TceLib.dir/flags.make

CMakeFiles/TceLib.dir/main.c.obj: CMakeFiles/TceLib.dir/flags.make
CMakeFiles/TceLib.dir/main.c.obj: CMakeFiles/TceLib.dir/includes_C.rsp
CMakeFiles/TceLib.dir/main.c.obj: C:/Users/Administrator/Documents/VASIKARAN/Monolithic\ project/main.c
CMakeFiles/TceLib.dir/main.c.obj: CMakeFiles/TceLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Administrator\Documents\VASIKARAN\Monolithic project\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TceLib.dir/main.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TceLib.dir/main.c.obj -MF CMakeFiles\TceLib.dir\main.c.obj.d -o CMakeFiles\TceLib.dir\main.c.obj -c "C:\Users\Administrator\Documents\VASIKARAN\Monolithic project\main.c"

CMakeFiles/TceLib.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/TceLib.dir/main.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\Administrator\Documents\VASIKARAN\Monolithic project\main.c" > CMakeFiles\TceLib.dir\main.c.i

CMakeFiles/TceLib.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/TceLib.dir/main.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\Administrator\Documents\VASIKARAN\Monolithic project\main.c" -o CMakeFiles\TceLib.dir\main.c.s

# Object files for target TceLib
TceLib_OBJECTS = \
"CMakeFiles/TceLib.dir/main.c.obj"

# External object files for target TceLib
TceLib_EXTERNAL_OBJECTS =

TceLib.exe: CMakeFiles/TceLib.dir/main.c.obj
TceLib.exe: CMakeFiles/TceLib.dir/build.make
TceLib.exe: CMakeFiles/TceLib.dir/linkLibs.rsp
TceLib.exe: CMakeFiles/TceLib.dir/objects1.rsp
TceLib.exe: CMakeFiles/TceLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\Administrator\Documents\VASIKARAN\Monolithic project\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable TceLib.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TceLib.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TceLib.dir/build: TceLib.exe
.PHONY : CMakeFiles/TceLib.dir/build

CMakeFiles/TceLib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TceLib.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TceLib.dir/clean

CMakeFiles/TceLib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Administrator\Documents\VASIKARAN\Monolithic project" "C:\Users\Administrator\Documents\VASIKARAN\Monolithic project" "C:\Users\Administrator\Documents\VASIKARAN\Monolithic project\build" "C:\Users\Administrator\Documents\VASIKARAN\Monolithic project\build" "C:\Users\Administrator\Documents\VASIKARAN\Monolithic project\build\CMakeFiles\TceLib.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/TceLib.dir/depend

