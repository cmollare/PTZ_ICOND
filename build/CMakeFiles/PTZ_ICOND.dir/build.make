# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/christophe/Laas/dev_PTZ/PTZ_ICOND

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/christophe/Laas/dev_PTZ/PTZ_ICOND/build

# Include any dependencies generated for this target.
include CMakeFiles/PTZ_ICOND.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PTZ_ICOND.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PTZ_ICOND.dir/flags.make

CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o: CMakeFiles/PTZ_ICOND.dir/flags.make
CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o: ../src/ControlPTZ.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/christophe/Laas/dev_PTZ/PTZ_ICOND/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o -c /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/ControlPTZ.cpp

CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/ControlPTZ.cpp > CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.i

CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/ControlPTZ.cpp -o CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.s

CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o.requires:
.PHONY : CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o.requires

CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o.provides: CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o.requires
	$(MAKE) -f CMakeFiles/PTZ_ICOND.dir/build.make CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o.provides.build
.PHONY : CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o.provides

CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o.provides.build: CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o

CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o: CMakeFiles/PTZ_ICOND.dir/flags.make
CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o: ../src/StreamRTSP.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/christophe/Laas/dev_PTZ/PTZ_ICOND/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o -c /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/StreamRTSP.cpp

CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/StreamRTSP.cpp > CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.i

CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/StreamRTSP.cpp -o CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.s

CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o.requires:
.PHONY : CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o.requires

CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o.provides: CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o.requires
	$(MAKE) -f CMakeFiles/PTZ_ICOND.dir/build.make CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o.provides.build
.PHONY : CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o.provides

CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o.provides.build: CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o

CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o: CMakeFiles/PTZ_ICOND.dir/flags.make
CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o: ../src/PTZ_ICOND.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/christophe/Laas/dev_PTZ/PTZ_ICOND/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o -c /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/PTZ_ICOND.cpp

CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/PTZ_ICOND.cpp > CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.i

CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/PTZ_ICOND.cpp -o CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.s

CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o.requires:
.PHONY : CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o.requires

CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o.provides: CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o.requires
	$(MAKE) -f CMakeFiles/PTZ_ICOND.dir/build.make CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o.provides.build
.PHONY : CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o.provides

CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o.provides.build: CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o

CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o: CMakeFiles/PTZ_ICOND.dir/flags.make
CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o: ../src/CorrectorPID.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/christophe/Laas/dev_PTZ/PTZ_ICOND/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o -c /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/CorrectorPID.cpp

CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/CorrectorPID.cpp > CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.i

CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/christophe/Laas/dev_PTZ/PTZ_ICOND/src/CorrectorPID.cpp -o CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.s

CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o.requires:
.PHONY : CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o.requires

CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o.provides: CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o.requires
	$(MAKE) -f CMakeFiles/PTZ_ICOND.dir/build.make CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o.provides.build
.PHONY : CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o.provides

CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o.provides.build: CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o

# Object files for target PTZ_ICOND
PTZ_ICOND_OBJECTS = \
"CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o" \
"CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o" \
"CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o" \
"CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o"

# External object files for target PTZ_ICOND
PTZ_ICOND_EXTERNAL_OBJECTS =

../bin/PTZ_ICOND: CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o
../bin/PTZ_ICOND: CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o
../bin/PTZ_ICOND: CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o
../bin/PTZ_ICOND: CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o
../bin/PTZ_ICOND: CMakeFiles/PTZ_ICOND.dir/build.make
../bin/PTZ_ICOND: CMakeFiles/PTZ_ICOND.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/PTZ_ICOND"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PTZ_ICOND.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PTZ_ICOND.dir/build: ../bin/PTZ_ICOND
.PHONY : CMakeFiles/PTZ_ICOND.dir/build

CMakeFiles/PTZ_ICOND.dir/requires: CMakeFiles/PTZ_ICOND.dir/src/ControlPTZ.cpp.o.requires
CMakeFiles/PTZ_ICOND.dir/requires: CMakeFiles/PTZ_ICOND.dir/src/StreamRTSP.cpp.o.requires
CMakeFiles/PTZ_ICOND.dir/requires: CMakeFiles/PTZ_ICOND.dir/src/PTZ_ICOND.cpp.o.requires
CMakeFiles/PTZ_ICOND.dir/requires: CMakeFiles/PTZ_ICOND.dir/src/CorrectorPID.cpp.o.requires
.PHONY : CMakeFiles/PTZ_ICOND.dir/requires

CMakeFiles/PTZ_ICOND.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PTZ_ICOND.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PTZ_ICOND.dir/clean

CMakeFiles/PTZ_ICOND.dir/depend:
	cd /home/christophe/Laas/dev_PTZ/PTZ_ICOND/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/christophe/Laas/dev_PTZ/PTZ_ICOND /home/christophe/Laas/dev_PTZ/PTZ_ICOND /home/christophe/Laas/dev_PTZ/PTZ_ICOND/build /home/christophe/Laas/dev_PTZ/PTZ_ICOND/build /home/christophe/Laas/dev_PTZ/PTZ_ICOND/build/CMakeFiles/PTZ_ICOND.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PTZ_ICOND.dir/depend

