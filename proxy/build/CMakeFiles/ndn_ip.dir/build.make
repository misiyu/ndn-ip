# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/misiyu/code/ndn-ip/proxy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/misiyu/code/ndn-ip/proxy/build

# Include any dependencies generated for this target.
include CMakeFiles/ndn_ip.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ndn_ip.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ndn_ip.dir/flags.make

CMakeFiles/ndn_ip.dir/main.cpp.o: CMakeFiles/ndn_ip.dir/flags.make
CMakeFiles/ndn_ip.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/misiyu/code/ndn-ip/proxy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ndn_ip.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndn_ip.dir/main.cpp.o -c /home/misiyu/code/ndn-ip/proxy/main.cpp

CMakeFiles/ndn_ip.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndn_ip.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/misiyu/code/ndn-ip/proxy/main.cpp > CMakeFiles/ndn_ip.dir/main.cpp.i

CMakeFiles/ndn_ip.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndn_ip.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/misiyu/code/ndn-ip/proxy/main.cpp -o CMakeFiles/ndn_ip.dir/main.cpp.s

CMakeFiles/ndn_ip.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/ndn_ip.dir/main.cpp.o.requires

CMakeFiles/ndn_ip.dir/main.cpp.o.provides: CMakeFiles/ndn_ip.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ndn_ip.dir/build.make CMakeFiles/ndn_ip.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ndn_ip.dir/main.cpp.o.provides

CMakeFiles/ndn_ip.dir/main.cpp.o.provides.build: CMakeFiles/ndn_ip.dir/main.cpp.o


CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o: CMakeFiles/ndn_ip.dir/flags.make
CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o: ../ip2ndn_proxy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/misiyu/code/ndn-ip/proxy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o -c /home/misiyu/code/ndn-ip/proxy/ip2ndn_proxy.cpp

CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/misiyu/code/ndn-ip/proxy/ip2ndn_proxy.cpp > CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.i

CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/misiyu/code/ndn-ip/proxy/ip2ndn_proxy.cpp -o CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.s

CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o.requires:

.PHONY : CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o.requires

CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o.provides: CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o.requires
	$(MAKE) -f CMakeFiles/ndn_ip.dir/build.make CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o.provides.build
.PHONY : CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o.provides

CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o.provides.build: CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o


CMakeFiles/ndn_ip.dir/connection.cpp.o: CMakeFiles/ndn_ip.dir/flags.make
CMakeFiles/ndn_ip.dir/connection.cpp.o: ../connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/misiyu/code/ndn-ip/proxy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ndn_ip.dir/connection.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndn_ip.dir/connection.cpp.o -c /home/misiyu/code/ndn-ip/proxy/connection.cpp

CMakeFiles/ndn_ip.dir/connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndn_ip.dir/connection.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/misiyu/code/ndn-ip/proxy/connection.cpp > CMakeFiles/ndn_ip.dir/connection.cpp.i

CMakeFiles/ndn_ip.dir/connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndn_ip.dir/connection.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/misiyu/code/ndn-ip/proxy/connection.cpp -o CMakeFiles/ndn_ip.dir/connection.cpp.s

CMakeFiles/ndn_ip.dir/connection.cpp.o.requires:

.PHONY : CMakeFiles/ndn_ip.dir/connection.cpp.o.requires

CMakeFiles/ndn_ip.dir/connection.cpp.o.provides: CMakeFiles/ndn_ip.dir/connection.cpp.o.requires
	$(MAKE) -f CMakeFiles/ndn_ip.dir/build.make CMakeFiles/ndn_ip.dir/connection.cpp.o.provides.build
.PHONY : CMakeFiles/ndn_ip.dir/connection.cpp.o.provides

CMakeFiles/ndn_ip.dir/connection.cpp.o.provides.build: CMakeFiles/ndn_ip.dir/connection.cpp.o


# Object files for target ndn_ip
ndn_ip_OBJECTS = \
"CMakeFiles/ndn_ip.dir/main.cpp.o" \
"CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o" \
"CMakeFiles/ndn_ip.dir/connection.cpp.o"

# External object files for target ndn_ip
ndn_ip_EXTERNAL_OBJECTS =

ndn_ip: CMakeFiles/ndn_ip.dir/main.cpp.o
ndn_ip: CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o
ndn_ip: CMakeFiles/ndn_ip.dir/connection.cpp.o
ndn_ip: CMakeFiles/ndn_ip.dir/build.make
ndn_ip: CMakeFiles/ndn_ip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/misiyu/code/ndn-ip/proxy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ndn_ip"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ndn_ip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ndn_ip.dir/build: ndn_ip

.PHONY : CMakeFiles/ndn_ip.dir/build

CMakeFiles/ndn_ip.dir/requires: CMakeFiles/ndn_ip.dir/main.cpp.o.requires
CMakeFiles/ndn_ip.dir/requires: CMakeFiles/ndn_ip.dir/ip2ndn_proxy.cpp.o.requires
CMakeFiles/ndn_ip.dir/requires: CMakeFiles/ndn_ip.dir/connection.cpp.o.requires

.PHONY : CMakeFiles/ndn_ip.dir/requires

CMakeFiles/ndn_ip.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ndn_ip.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ndn_ip.dir/clean

CMakeFiles/ndn_ip.dir/depend:
	cd /home/misiyu/code/ndn-ip/proxy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/misiyu/code/ndn-ip/proxy /home/misiyu/code/ndn-ip/proxy /home/misiyu/code/ndn-ip/proxy/build /home/misiyu/code/ndn-ip/proxy/build /home/misiyu/code/ndn-ip/proxy/build/CMakeFiles/ndn_ip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ndn_ip.dir/depend
