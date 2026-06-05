cmake_minimum_required(VERSION 3.15)

project(stb_image)

add_library(stb_image STATIC
    stb_image.cpp
)

target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(stb_image PRIVATE
    STBI_NO_SIMD
)