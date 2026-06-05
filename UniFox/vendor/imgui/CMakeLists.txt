cmake_minimum_required(VERSION 3.15)

project(imgui LANGUAGES CXX)

add_library(imgui STATIC
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
)

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(imgui PUBLIC cxx_std_11)

# Optional: enable Win32 + OpenGL backend files if you want them here too
# (otherwise compile them in your engine target)

target_sources(imgui PRIVATE
    backends/imgui_impl_glfw.cpp
    backends/imgui_impl_opengl3.cpp
)