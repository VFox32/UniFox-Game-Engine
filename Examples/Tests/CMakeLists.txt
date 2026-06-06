project(Tests)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_executable(Tests)

target_sources(Tests
    PRIVATE
        src/main.cpp
        src/Sandbox2D.cpp
        src/Sandbox3D.cpp
)

target_include_directories(Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(Tests
    PRIVATE
        UniFox
)

add_custom_command(
    TARGET Tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:Tests>/assets

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:Tests>/assets
)