cmake_minimum_required(VERSION 3.15)
project(AppProject)

# 1. Set C++ Standard (usually needed for ImGui/SDL3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Add your -DRELEASE define
add_compile_definitions(RELEASE)

# 3. Define the executable and list the source files
# This replaces your "%cd%\src\*.cpp" and the manual list of ImGui files
add_executable(App

	# Main
    src/main.cpp

	# ImGui core
	dep/include/imgui/imgui.cpp
	dep/include/imgui/imgui_draw.cpp
	dep/include/imgui/imgui_tables.cpp
	dep/include/imgui/imgui_widgets.cpp
	dep/include/imgui/imgui_demo.cpp
	
	# ImGui backends
	dep/include/imgui/imgui_impl_sdl3.cpp
    dep/include/imgui/imgui_impl_opengl3.cpp
)

# 4. Include Directories (Replaces your %includes%)
target_include_directories(App PRIVATE 
    src 
    dep/include
)

# 5. Link Directories (Replaces your %links% -L paths)
target_link_directories(App PRIVATE 
    src 
    dep/lib
)

# 6. Link Libraries (Replaces your -l flags)
# Note: You don't need to list all the system ones (kernel32, etc.) 
# most of the time as the compiler adds them automatically.
target_link_libraries(App PRIVATE 
    opengl32
	user32
	shell32
	gdi32
	kernel32
	advapi32
	ole32
	oleaut32
	uuid
	odbc32
	odbccp32
	glew32
	SDL3.dll
)
