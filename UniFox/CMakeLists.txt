add_library(UniFox SHARED
    src/UniFox/Application.cpp
)

target_compile_definitions(UniFox PRIVATE
    UF_BUILD_DLL
    UF_PLATFORM_WINDOWS
)

target_include_directories(UniFox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)