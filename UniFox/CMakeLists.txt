project(UniFox)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)

add_library(UniFox SHARED
    src/UniFox/Application.cpp
    src/UniFox/Log.cpp
    src/ufpch.cpp
    src/UniFox/Platform/Windows/WindowsWindow.cpp
)

target_compile_definitions(UniFox PRIVATE
    UF_BUILD_DLL
    UF_PLATFORM_WINDOWS
)

target_include_directories(UniFox
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include
)

add_dependencies(${PROJECT_NAME} spdlog)

target_link_libraries(UniFox
    PRIVATE
        spdlog::spdlog
        glfw
        opengl32.lib
)

target_precompile_headers(UniFox
    PRIVATE
        src/ufpch.h
)