project(Voxels)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_executable(Voxels)

target_sources(Voxels
    PRIVATE
        src/main.cpp
        src/Terrain.cpp
)

target_include_directories(Voxels PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(Voxels
    PRIVATE
        UniFox
)

add_custom_command(
    TARGET Voxels POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:Voxels>/assets

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:Voxels>/assets
)