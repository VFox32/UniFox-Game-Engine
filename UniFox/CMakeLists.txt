project(UniFox)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

option(GLFW_BUILD_SHARED_LIBS "Build GLFW shared" OFF)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glm)

add_library(UniFox STATIC
    src/ufpch.cpp

    src/UniFox/Core/Application.cpp
    src/UniFox/Core/Log.cpp
    src/UniFox/Core/Layer.cpp
    src/UniFox/Core/LayerStack.cpp

    src/UniFox/ImGui/ImGuiLayer.cpp

    src/UniFox/Platform/Windows/WindowsInput.cpp
    src/UniFox/Platform/Windows/WindowsWindow.cpp

    src/UniFox/Platform/OpenGL/OpenGLContext.cpp
    src/UniFox/Platform/OpenGL/OpenGLBuffer.cpp
    src/UniFox/Platform/OpenGL/OpenGLShader.cpp
    src/UniFox/Platform/OpenGL/OpenGLVertexArray.cpp
    src/UniFox/Platform/OpenGL/OpenGLRendererAPI.cpp

    src/UniFox/Renderer/Shader.cpp
    src/UniFox/Renderer/Buffer.cpp
    src/UniFox/Renderer/Renderer.cpp
    src/UniFox/Renderer/VertexArray.cpp
    src/UniFox/Renderer/RendererAPI.cpp
    src/UniFox/Renderer/RenderCommand.cpp
    src/UniFox/Renderer/OrthographicCamera.cpp
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
    PUBLIC
        imgui
    PRIVATE
        spdlog::spdlog_header_only
        glfw
        opengl32.lib
        glad
        glm
)

target_precompile_headers(UniFox
    PRIVATE
        src/ufpch.h
)