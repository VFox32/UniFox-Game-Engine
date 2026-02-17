project(UniFox)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glm)

add_library(UniFox SHARED
    src/UniFox/Application.cpp
    src/UniFox/Log.cpp
    src/ufpch.cpp
    src/UniFox/Platform/Windows/WindowsWindow.cpp
    src/UniFox/Layer.cpp
    src/UniFox/LayerStack.cpp
    src/UniFox/ImGui/ImGuiLayer.cpp
    src/UniFox/Platform/OpenGL/ImGuiOpenGLRenderer.cpp
    src/UniFox/Platform/Windows/WindowsInput.cpp
)

target_compile_definitions(UniFox PRIVATE
    UF_BUILD_DLL
    UF_PLATFORM_WINDOWS
    GLFW_INCLUDE_NONE
)

target_include_directories(UniFox
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGui
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
)

add_dependencies(${PROJECT_NAME} spdlog)
add_dependencies(${PROJECT_NAME} glad)
add_dependencies(${PROJECT_NAME} imgui)
add_dependencies(${PROJECT_NAME} glm)

target_link_libraries(UniFox
    PRIVATE
        spdlog::spdlog
        glfw
        opengl32.lib
        glad
        imgui
        glm
)

target_precompile_headers(UniFox
    PRIVATE
        src/ufpch.h
)