project(UniFox)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

option(GLFW_BUILD_SHARED_LIBS "Build GLFW shared" OFF)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/stb_image)

set(CORE_SOURCE
    src/UniFox/Core/Application.cpp
    src/UniFox/Core/Log.cpp
    src/UniFox/Core/Layer.cpp
    src/UniFox/Core/LayerStack.cpp
    src/UniFox/Core/Time.cpp

    src/UniFox/ImGui/ImGuiLayer.cpp
)

set(UTIL_SOURCE
    src/UniFox/Util/StreamWriter.cpp
    src/UniFox/Util/StreamReader.cpp
    src/UniFox/Util/FileStream.cpp
    src/UniFox/Util/MemoryStream.cpp
)

set(RENDERER_SOURCE
    src/UniFox/Renderer/Shader.cpp
    src/UniFox/Renderer/Buffer.cpp
    src/UniFox/Renderer/Renderer.cpp
    src/UniFox/Renderer/Renderer2D.cpp
    src/UniFox/Renderer/VertexArray.cpp
    src/UniFox/Renderer/RendererAPI.cpp
    src/UniFox/Renderer/RenderCommand.cpp
    src/UniFox/Renderer/Texture.cpp
    src/UniFox/Renderer/Camera.cpp
    src/UniFox/Renderer/CameraController.cpp
)

set(PLATFORM_SOURCE
    src/UniFox/Platform/Windows/WindowsInput.cpp
    src/UniFox/Platform/Windows/WindowsWindow.cpp

    src/UniFox/Platform/OpenGL/OpenGLContext.cpp
    src/UniFox/Platform/OpenGL/OpenGLBuffer.cpp
    src/UniFox/Platform/OpenGL/OpenGLShader.cpp
    src/UniFox/Platform/OpenGL/OpenGLVertexArray.cpp
    src/UniFox/Platform/OpenGL/OpenGLRendererAPI.cpp
    src/UniFox/Platform/OpenGL/OpenGLTexture.cpp
)

add_library(UniFox STATIC
    src/ufpch.cpp
    ${CORE_SOURCE}
    ${UTIL_SOURCE}
    ${RENDERER_SOURCE}
    ${PLATFORM_SOURCE}
)

target_compile_features(UniFox PUBLIC cxx_std_23)

target_compile_definitions(UniFox PRIVATE
    GLFW_INCLUDE_NONE

    UF_ENABLE_LOGGING
    $<$<CONFIG:Debug>:UF_DEBUG>
    $<$<CONFIG:Debug>:UF_ENABLE_ASSERTS>
    $<$<CONFIG:Debug>:UF_ENABLE_PROFILING>

    $<$<CONFIG:Release>:UF_RELEASE>
)

#target_compile_definitions(UniFox PRIVATE
#    GLFW_INCLUDE_NONE
#    UF_DEBUG
#)

target_include_directories(UniFox
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image
)

find_package(OpenGL REQUIRED)

target_link_libraries(UniFox
    PUBLIC
        imgui
    PRIVATE
        glfw
        glm
        glad
        spdlog_header_only
        stb_image
        OpenGL::GL
)

target_precompile_headers(UniFox
    PRIVATE
        src/ufpch.h
)