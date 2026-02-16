cmake_minimum_required(VERSION 3.16)

project(Sandbox)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_subdirectory(UniFox)
add_subdirectory(Sandbox)