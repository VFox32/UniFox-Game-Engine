cmake_minimum_required(VERSION 3.16)

project(Sandbox)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(UniFox)

add_subdirectory(Examples/Tests)
add_subdirectory(Examples/Chess)
add_subdirectory(Examples/Voxels)