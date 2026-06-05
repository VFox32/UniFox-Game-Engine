project(Sandbox)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_executable(Sandbox)

target_sources(Sandbox PRIVATE
    src/Sandbox.cpp
    src/Sandbox2D.cpp
    src/Sandbox3D.cpp
    src/Terrain.cpp
    src/Chess/Chess.cpp
    src/Chess/Moves.cpp
    src/Chess/Board.cpp
)

target_include_directories(Sandbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(Sandbox PRIVATE UniFox)

add_custom_command(
    TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:Sandbox>/assets

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:Sandbox>/assets
)