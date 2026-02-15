project(UniFox)

add_subdirectory(vendor/spdlog)

add_library(UniFox SHARED
    src/UniFox/Application.cpp
    src/UniFox/Log.cpp
)

target_compile_definitions(UniFox PRIVATE
    UF_BUILD_DLL
    UF_PLATFORM_WINDOWS
)

target_include_directories(UniFox
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
)

add_dependencies(${PROJECT_NAME} spdlog)

target_link_libraries(UniFox
    PRIVATE
        spdlog::spdlog    
)