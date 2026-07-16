project(GUI)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_executable(GUI)

target_sources(GUI
    PRIVATE
        src/main.cpp
        src/GUI.cpp
        src/Widget.cpp
        src/Container.cpp
        src/UIManager.cpp
)

target_include_directories(GUI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(GUI
    PRIVATE
        UniFox
)

add_custom_command(
    TARGET GUI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:GUI>/assets

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:GUI>/assets
)