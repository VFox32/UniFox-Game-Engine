project(Sandbox)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_executable(Sandbox)

target_sources(Sandbox PRIVATE
    src/Sandbox.cpp
    src/Sandbox2D.cpp
)

target_compile_definitions(
    Sandbox PRIVATE UF_PLATFORM_WINDOWS
)

target_include_directories(Sandbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(Sandbox PRIVATE UniFox)

add_custom_command(
    TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:Sandbox>
)

#add_custom_command(TARGET Sandbox POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_FILE:UniFox>
#        $<TARGET_FILE_DIR:Sandbox>
#)