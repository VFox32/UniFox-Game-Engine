project(Chess)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_executable(Chess)

target_sources(Chess
    PRIVATE
        src/main.cpp
        src/Chess.cpp
        src/Moves.cpp
        src/Board.cpp
)

target_include_directories(Chess PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(Chess
    PRIVATE
        UniFox
)

add_custom_command(
    TARGET Chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:Chess>/assets

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:Chess>/assets
)