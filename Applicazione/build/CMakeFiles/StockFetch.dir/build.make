# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build

# Include any dependencies generated for this target.
include CMakeFiles/StockFetch.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/StockFetch.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/StockFetch.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StockFetch.dir/flags.make

StockFetch_autogen/timestamp: /opt/local/libexec/qt6/./libexec/moc
StockFetch_autogen/timestamp: /opt/local/libexec/qt6/./libexec/uic
StockFetch_autogen/timestamp: CMakeFiles/StockFetch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target StockFetch"
	/opt/local/bin/cmake -E cmake_autogen /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/CMakeFiles/StockFetch_autogen.dir/AutogenInfo.json ""
	/opt/local/bin/cmake -E touch /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/StockFetch_autogen/timestamp

CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.o: CMakeFiles/StockFetch.dir/flags.make
CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.o: StockFetch_autogen/mocs_compilation.cpp
CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.o: CMakeFiles/StockFetch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.o -MF CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.o -c /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/StockFetch_autogen/mocs_compilation.cpp

CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/StockFetch_autogen/mocs_compilation.cpp > CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.i

CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/StockFetch_autogen/mocs_compilation.cpp -o CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.s

CMakeFiles/StockFetch.dir/order.cpp.o: CMakeFiles/StockFetch.dir/flags.make
CMakeFiles/StockFetch.dir/order.cpp.o: /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/order.cpp
CMakeFiles/StockFetch.dir/order.cpp.o: CMakeFiles/StockFetch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/StockFetch.dir/order.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StockFetch.dir/order.cpp.o -MF CMakeFiles/StockFetch.dir/order.cpp.o.d -o CMakeFiles/StockFetch.dir/order.cpp.o -c /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/order.cpp

CMakeFiles/StockFetch.dir/order.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/StockFetch.dir/order.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/order.cpp > CMakeFiles/StockFetch.dir/order.cpp.i

CMakeFiles/StockFetch.dir/order.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/StockFetch.dir/order.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/order.cpp -o CMakeFiles/StockFetch.dir/order.cpp.s

CMakeFiles/StockFetch.dir/json_read_stocks.c.o: CMakeFiles/StockFetch.dir/flags.make
CMakeFiles/StockFetch.dir/json_read_stocks.c.o: /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/json_read_stocks.c
CMakeFiles/StockFetch.dir/json_read_stocks.c.o: CMakeFiles/StockFetch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/StockFetch.dir/json_read_stocks.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/StockFetch.dir/json_read_stocks.c.o -MF CMakeFiles/StockFetch.dir/json_read_stocks.c.o.d -o CMakeFiles/StockFetch.dir/json_read_stocks.c.o -c /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/json_read_stocks.c

CMakeFiles/StockFetch.dir/json_read_stocks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/StockFetch.dir/json_read_stocks.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/json_read_stocks.c > CMakeFiles/StockFetch.dir/json_read_stocks.c.i

CMakeFiles/StockFetch.dir/json_read_stocks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/StockFetch.dir/json_read_stocks.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/json_read_stocks.c -o CMakeFiles/StockFetch.dir/json_read_stocks.c.s

CMakeFiles/StockFetch.dir/read_file_implementation.c.o: CMakeFiles/StockFetch.dir/flags.make
CMakeFiles/StockFetch.dir/read_file_implementation.c.o: /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/read_file_implementation.c
CMakeFiles/StockFetch.dir/read_file_implementation.c.o: CMakeFiles/StockFetch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/StockFetch.dir/read_file_implementation.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/StockFetch.dir/read_file_implementation.c.o -MF CMakeFiles/StockFetch.dir/read_file_implementation.c.o.d -o CMakeFiles/StockFetch.dir/read_file_implementation.c.o -c /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/read_file_implementation.c

CMakeFiles/StockFetch.dir/read_file_implementation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/StockFetch.dir/read_file_implementation.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/read_file_implementation.c > CMakeFiles/StockFetch.dir/read_file_implementation.c.i

CMakeFiles/StockFetch.dir/read_file_implementation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/StockFetch.dir/read_file_implementation.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/read_file_implementation.c -o CMakeFiles/StockFetch.dir/read_file_implementation.c.s

CMakeFiles/StockFetch.dir/SQL_create.c.o: CMakeFiles/StockFetch.dir/flags.make
CMakeFiles/StockFetch.dir/SQL_create.c.o: /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/SQL_create.c
CMakeFiles/StockFetch.dir/SQL_create.c.o: CMakeFiles/StockFetch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/StockFetch.dir/SQL_create.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/StockFetch.dir/SQL_create.c.o -MF CMakeFiles/StockFetch.dir/SQL_create.c.o.d -o CMakeFiles/StockFetch.dir/SQL_create.c.o -c /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/SQL_create.c

CMakeFiles/StockFetch.dir/SQL_create.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/StockFetch.dir/SQL_create.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/SQL_create.c > CMakeFiles/StockFetch.dir/SQL_create.c.i

CMakeFiles/StockFetch.dir/SQL_create.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/StockFetch.dir/SQL_create.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/SQL_create.c -o CMakeFiles/StockFetch.dir/SQL_create.c.s

CMakeFiles/StockFetch.dir/SQL_read.c.o: CMakeFiles/StockFetch.dir/flags.make
CMakeFiles/StockFetch.dir/SQL_read.c.o: /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/SQL_read.c
CMakeFiles/StockFetch.dir/SQL_read.c.o: CMakeFiles/StockFetch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/StockFetch.dir/SQL_read.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/StockFetch.dir/SQL_read.c.o -MF CMakeFiles/StockFetch.dir/SQL_read.c.o.d -o CMakeFiles/StockFetch.dir/SQL_read.c.o -c /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/SQL_read.c

CMakeFiles/StockFetch.dir/SQL_read.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/StockFetch.dir/SQL_read.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/SQL_read.c > CMakeFiles/StockFetch.dir/SQL_read.c.i

CMakeFiles/StockFetch.dir/SQL_read.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/StockFetch.dir/SQL_read.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/SQL_read.c -o CMakeFiles/StockFetch.dir/SQL_read.c.s

CMakeFiles/StockFetch.dir/Stock_Data.c.o: CMakeFiles/StockFetch.dir/flags.make
CMakeFiles/StockFetch.dir/Stock_Data.c.o: /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/Stock_Data.c
CMakeFiles/StockFetch.dir/Stock_Data.c.o: CMakeFiles/StockFetch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/StockFetch.dir/Stock_Data.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/StockFetch.dir/Stock_Data.c.o -MF CMakeFiles/StockFetch.dir/Stock_Data.c.o.d -o CMakeFiles/StockFetch.dir/Stock_Data.c.o -c /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/Stock_Data.c

CMakeFiles/StockFetch.dir/Stock_Data.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/StockFetch.dir/Stock_Data.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/Stock_Data.c > CMakeFiles/StockFetch.dir/Stock_Data.c.i

CMakeFiles/StockFetch.dir/Stock_Data.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/StockFetch.dir/Stock_Data.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/Stock_Data.c -o CMakeFiles/StockFetch.dir/Stock_Data.c.s

# Object files for target StockFetch
StockFetch_OBJECTS = \
"CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/StockFetch.dir/order.cpp.o" \
"CMakeFiles/StockFetch.dir/json_read_stocks.c.o" \
"CMakeFiles/StockFetch.dir/read_file_implementation.c.o" \
"CMakeFiles/StockFetch.dir/SQL_create.c.o" \
"CMakeFiles/StockFetch.dir/SQL_read.c.o" \
"CMakeFiles/StockFetch.dir/Stock_Data.c.o"

# External object files for target StockFetch
StockFetch_EXTERNAL_OBJECTS =

StockFetch: CMakeFiles/StockFetch.dir/StockFetch_autogen/mocs_compilation.cpp.o
StockFetch: CMakeFiles/StockFetch.dir/order.cpp.o
StockFetch: CMakeFiles/StockFetch.dir/json_read_stocks.c.o
StockFetch: CMakeFiles/StockFetch.dir/read_file_implementation.c.o
StockFetch: CMakeFiles/StockFetch.dir/SQL_create.c.o
StockFetch: CMakeFiles/StockFetch.dir/SQL_read.c.o
StockFetch: CMakeFiles/StockFetch.dir/Stock_Data.c.o
StockFetch: CMakeFiles/StockFetch.dir/build.make
StockFetch: /opt/local/libexec/qt6/lib/QtWidgets.framework/Versions/A/QtWidgets
StockFetch: /opt/local/lib/libcurl.dylib
StockFetch: /opt/local/lib/libsqlite3.dylib
StockFetch: /opt/local/libexec/qt6/lib/QtGui.framework/Versions/A/QtGui
StockFetch: /opt/local/libexec/qt6/lib/QtCore.framework/Versions/A/QtCore
StockFetch: CMakeFiles/StockFetch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable StockFetch"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StockFetch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StockFetch.dir/build: StockFetch
.PHONY : CMakeFiles/StockFetch.dir/build

CMakeFiles/StockFetch.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/StockFetch.dir/cmake_clean.cmake
.PHONY : CMakeFiles/StockFetch.dir/clean

CMakeFiles/StockFetch.dir/depend: StockFetch_autogen/timestamp
	cd /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build /Users/matti/Documents/GitHub/Stock_Fetch/Applicazione/build/CMakeFiles/StockFetch.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/StockFetch.dir/depend

