# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\cmake-build-debug-mingw"

# Include any dependencies generated for this target.
include src/Engine/CMakeFiles/engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/Engine/CMakeFiles/engine.dir/compiler_depend.make

# Include the progress variables for this target.
include src/Engine/CMakeFiles/engine.dir/progress.make

# Include the compile flags for this target's objects.
include src/Engine/CMakeFiles/engine.dir/flags.make

src/Engine/CMakeFiles/engine.dir/Mesh.cpp.obj: src/Engine/CMakeFiles/engine.dir/flags.make
src/Engine/CMakeFiles/engine.dir/Mesh.cpp.obj: src/Engine/CMakeFiles/engine.dir/includes_CXX.rsp
src/Engine/CMakeFiles/engine.dir/Mesh.cpp.obj: C:/Users/Tomasz\ Kulwicki/Desktop/UJ/Grafika\ 3D/3d23-main/src/Engine/Mesh.cpp
src/Engine/CMakeFiles/engine.dir/Mesh.cpp.obj: src/Engine/CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\cmake-build-debug-mingw\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Engine/CMakeFiles/engine.dir/Mesh.cpp.obj"
	cd /d C:\Users\TOMASZ~1\Desktop\UJ\GRAFIK~1\3D23-M~1\CMAKE-~1\src\Engine && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Engine/CMakeFiles/engine.dir/Mesh.cpp.obj -MF CMakeFiles\engine.dir\Mesh.cpp.obj.d -o CMakeFiles\engine.dir\Mesh.cpp.obj -c "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\src\Engine\Mesh.cpp"

src/Engine/CMakeFiles/engine.dir/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/Mesh.cpp.i"
	cd /d C:\Users\TOMASZ~1\Desktop\UJ\GRAFIK~1\3D23-M~1\CMAKE-~1\src\Engine && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\src\Engine\Mesh.cpp" > CMakeFiles\engine.dir\Mesh.cpp.i

src/Engine/CMakeFiles/engine.dir/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/Mesh.cpp.s"
	cd /d C:\Users\TOMASZ~1\Desktop\UJ\GRAFIK~1\3D23-M~1\CMAKE-~1\src\Engine && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\src\Engine\Mesh.cpp" -o CMakeFiles\engine.dir\Mesh.cpp.s

src/Engine/CMakeFiles/engine.dir/Material.cpp.obj: src/Engine/CMakeFiles/engine.dir/flags.make
src/Engine/CMakeFiles/engine.dir/Material.cpp.obj: src/Engine/CMakeFiles/engine.dir/includes_CXX.rsp
src/Engine/CMakeFiles/engine.dir/Material.cpp.obj: C:/Users/Tomasz\ Kulwicki/Desktop/UJ/Grafika\ 3D/3d23-main/src/Engine/Material.cpp
src/Engine/CMakeFiles/engine.dir/Material.cpp.obj: src/Engine/CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\cmake-build-debug-mingw\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/Engine/CMakeFiles/engine.dir/Material.cpp.obj"
	cd /d C:\Users\TOMASZ~1\Desktop\UJ\GRAFIK~1\3D23-M~1\CMAKE-~1\src\Engine && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Engine/CMakeFiles/engine.dir/Material.cpp.obj -MF CMakeFiles\engine.dir\Material.cpp.obj.d -o CMakeFiles\engine.dir\Material.cpp.obj -c "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\src\Engine\Material.cpp"

src/Engine/CMakeFiles/engine.dir/Material.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/Material.cpp.i"
	cd /d C:\Users\TOMASZ~1\Desktop\UJ\GRAFIK~1\3D23-M~1\CMAKE-~1\src\Engine && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\src\Engine\Material.cpp" > CMakeFiles\engine.dir\Material.cpp.i

src/Engine/CMakeFiles/engine.dir/Material.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/Material.cpp.s"
	cd /d C:\Users\TOMASZ~1\Desktop\UJ\GRAFIK~1\3D23-M~1\CMAKE-~1\src\Engine && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\src\Engine\Material.cpp" -o CMakeFiles\engine.dir\Material.cpp.s

# Object files for target engine
engine_OBJECTS = \
"CMakeFiles/engine.dir/Mesh.cpp.obj" \
"CMakeFiles/engine.dir/Material.cpp.obj"

# External object files for target engine
engine_EXTERNAL_OBJECTS = \
"C:/Users/Tomasz Kulwicki/Desktop/UJ/Grafika 3D/3d23-main/cmake-build-debug-mingw/CMakeFiles/glad.dir/src/3rdParty/glad/glad_4_6/glad/src/gl.c.obj"

src/Engine/libengine.a: src/Engine/CMakeFiles/engine.dir/Mesh.cpp.obj
src/Engine/libengine.a: src/Engine/CMakeFiles/engine.dir/Material.cpp.obj
src/Engine/libengine.a: CMakeFiles/glad.dir/src/3rdParty/glad/glad_4_6/glad/src/gl.c.obj
src/Engine/libengine.a: src/Engine/CMakeFiles/engine.dir/build.make
src/Engine/libengine.a: src/Engine/CMakeFiles/engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\cmake-build-debug-mingw\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libengine.a"
	cd /d C:\Users\TOMASZ~1\Desktop\UJ\GRAFIK~1\3D23-M~1\CMAKE-~1\src\Engine && $(CMAKE_COMMAND) -P CMakeFiles\engine.dir\cmake_clean_target.cmake
	cd /d C:\Users\TOMASZ~1\Desktop\UJ\GRAFIK~1\3D23-M~1\CMAKE-~1\src\Engine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\engine.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Engine/CMakeFiles/engine.dir/build: src/Engine/libengine.a
.PHONY : src/Engine/CMakeFiles/engine.dir/build

src/Engine/CMakeFiles/engine.dir/clean:
	cd /d C:\Users\TOMASZ~1\Desktop\UJ\GRAFIK~1\3D23-M~1\CMAKE-~1\src\Engine && $(CMAKE_COMMAND) -P CMakeFiles\engine.dir\cmake_clean.cmake
.PHONY : src/Engine/CMakeFiles/engine.dir/clean

src/Engine/CMakeFiles/engine.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main" "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\src\Engine" "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\cmake-build-debug-mingw" "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\cmake-build-debug-mingw\src\Engine" "C:\Users\Tomasz Kulwicki\Desktop\UJ\Grafika 3D\3d23-main\cmake-build-debug-mingw\src\Engine\CMakeFiles\engine.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : src/Engine/CMakeFiles/engine.dir/depend

